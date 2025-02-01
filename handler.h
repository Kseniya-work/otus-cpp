#pragma once

#include <algorithm>
#include <chrono>
#include <memory>
#include <sstream>
#include <string>
#include <vector>


#include <ctime>
#include <iomanip>
#include <iostream>//TODO delete

template <typename Storage, typename Logger>
class Handler
{
private:
    using StoragePtr = std::unique_ptr<Storage>;
    using Loggers = std::vector<std::shared_ptr<Logger>>;

    StoragePtr storage_;
    Loggers loggers_;

    int staticBlockSize_;
    int staticBlockSizeCurrent_;
    bool isBulkStart_;
    std::string endString_;
    std::string dynamicBlockBeginSymbol_;
    std::string dynamicBlockEndSymbol_;

public:
    Handler(StoragePtr storage,
            const Loggers & loggers,
            const int staticBlockSize,
            const std::string endString = "EOF",
            const std::string dynamicBlockBeginSymbol = "{",
            const std::string dynamicBlockEndSymbol = "}")
    : storage_(std::move(storage))
    , loggers_(loggers)
    , staticBlockSize_(staticBlockSize)
    , staticBlockSizeCurrent_(staticBlockSize)
    , isBulkStart_(true)
    , endString_(endString)
    , dynamicBlockBeginSymbol_(dynamicBlockBeginSymbol)
    , dynamicBlockEndSymbol_(dynamicBlockEndSymbol)
    {}

    void read(std::istream& istream);
    void write(std::chrono::time_point<std::chrono::steady_clock> ) const;

private:
    void drop(std::chrono::time_point<std::chrono::steady_clock> time);
};


template <typename Storage, typename Logger>
void Handler<Storage, Logger>::write(std::chrono::time_point<std::chrono::steady_clock> ) const
{
    if (storage_->empty())
        return;

    std::ostringstream bulk;
    bulk << "bulk: ";
    for (auto it = storage_->begin(); it != storage_->end(); ++it)
    {
        bulk << (it != storage_->begin() ? ", " : "") << *it;
    }
    bulk << std::endl;

    // std::cout << time.time_since_epoch();
    std::for_each(loggers_.begin(), loggers_.end(), [&bulk](const auto & logger){
        logger->write(bulk);});
}

template <typename Storage, typename Logger>
void Handler<Storage, Logger>::drop(std::chrono::time_point<std::chrono::steady_clock> time)
{
    write(time);
    storage_->clear();
    isBulkStart_ = true;
    staticBlockSizeCurrent_ = staticBlockSize_;
}

template <typename Storage, typename Logger>
void Handler<Storage, Logger>::read(std::istream& istream)
{
    bool isDynamicBlock = false;
    int openBracketsCount = 0;
    std::chrono::time_point<std::chrono::steady_clock> fstCmdTime;

    for(std::string line; std::getline(istream, line);)
    {
        if (isBulkStart_)
            fstCmdTime = std::chrono::steady_clock::now();

        if (line == endString_)
        {
            if (!isDynamicBlock)
                drop(fstCmdTime);
            break;
        }
        else if (line == dynamicBlockBeginSymbol_)
        {
            openBracketsCount++;
            if (openBracketsCount == 1)
            {
                isDynamicBlock = true;
                drop(fstCmdTime);
            }
            continue;
        }
        else if ((line == dynamicBlockEndSymbol_) && (openBracketsCount > 0))
        {
            openBracketsCount--;
            if (openBracketsCount == 0)
            {
                isDynamicBlock = false;
                drop(fstCmdTime);
            }
            continue;
        }

        if (isDynamicBlock || (staticBlockSizeCurrent_ > 0))
        {
            storage_->add(line);
            isBulkStart_ = false;
        }

        if (!isDynamicBlock && (staticBlockSizeCurrent_ > 0))
        {
            staticBlockSizeCurrent_--;
            if (staticBlockSizeCurrent_ == 0)
            {
                drop(fstCmdTime);
            }
        }
    }
}