#pragma once

#include <algorithm>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

template <typename Storage, typename Logger>
class Handler
{
private:
    using StoragePtr = std::unique_ptr<Storage>;
    using Loggers = std::vector<std::shared_ptr<Logger>>;

    int staticBlockSize_;
    StoragePtr storage_;
    Loggers loggers_;
    std::string endString_;
    std::string dynamicBlockBeginSymbol_;
    std::string dynamicBlockEndSymbol_;

public:
    Handler(const int staticBlockSize,
            StoragePtr storage,
            const Loggers & loggers,
            const std::string endString = "EOF",
            const std::string dynamicBlockBeginSymbol = "{",
            const std::string dynamicBlockEndSymbol = "}")
    : staticBlockSize_(staticBlockSize)
    , storage_(std::move(storage))
    , loggers_(loggers)
    , endString_(endString)
    , dynamicBlockBeginSymbol_(dynamicBlockBeginSymbol)
    , dynamicBlockEndSymbol_(dynamicBlockEndSymbol)
    {}

    void read(std::istream& istream);
    void write() const;
};


template <typename Storage, typename Logger>
void Handler<Storage, Logger>::write() const
{
    std::ostringstream bulk;
    bulk << "bulk: ";
    for (auto it = storage_->begin(); it != storage_->end(); ++it)
    {
        bulk << (it != storage_->begin() ? ", " : "") << *it;
    }
    bulk << std::endl;

    std::for_each(loggers_.begin(), loggers_.end(), [&bulk](const auto & logger){
        logger->write(bulk);});
}

template <typename Storage, typename Logger>
void Handler<Storage, Logger>::read(std::istream& istream)
{
    static bool isDynamicBlockStarted = false;
    static int openBracketsCount = 0;
    int staticBlockSizeCurrent = staticBlockSize_;

    for(std::string line; std::getline(istream, line);)
    {
        if (line == endString_)
        {
            if (!isDynamicBlockStarted && !storage_->empty())
                write();
            break;
        }
        else if (line == dynamicBlockBeginSymbol_)
        {
            openBracketsCount++;
            isDynamicBlockStarted = true;

            if ((openBracketsCount == 1) && !storage_->empty())
            {
                write();
                storage_->clear();
                staticBlockSizeCurrent = staticBlockSize_;
            }
            continue;
        }
        else if (line == dynamicBlockEndSymbol_ && openBracketsCount > 0)
        {
            openBracketsCount--;
            if (openBracketsCount == 0)
            {
                isDynamicBlockStarted = false;
                write();
                storage_->clear();
            }
            continue;
        }

        storage_->add(line);
        if (!isDynamicBlockStarted && staticBlockSizeCurrent == 1)
        {
            write();
            storage_->clear();
            staticBlockSizeCurrent = staticBlockSize_;
        }
        else if (!isDynamicBlockStarted && staticBlockSizeCurrent != 0)
        {
            staticBlockSizeCurrent--;
        }
    }
}