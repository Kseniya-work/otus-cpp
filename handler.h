#pragma once

#include <algorithm>
#include <chrono>
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
    using time_type = std::chrono::time_point<std::chrono::steady_clock>;

    StoragePtr storage_;
    Loggers loggers_;
    std::array<std::string, 3> smbl_;

    int staticBlockSize_;
    int staticBlockSizeCurrent_;
    bool isBulkStart_;

public:
    Handler(StoragePtr storage,
            const Loggers & loggers,
            const int staticBlockSize,
            const std::array<std::string, 3> smbl = {"{", "}", "EOF"})
    : storage_(std::move(storage))
    , loggers_(loggers)
    , smbl_(smbl)
    , staticBlockSize_(staticBlockSize)
    , staticBlockSizeCurrent_(staticBlockSize)
    , isBulkStart_(true)
    {}

    void read(std::istream& istream);
    void write(const time_type time) const;

private:
    void drop(const time_type time);
};


template <typename Storage, typename Logger>
void Handler<Storage, Logger>::write(const time_type time) const
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

    for (const auto & logger : loggers_)
        logger->write(bulk, time);
}

template <typename Storage, typename Logger>
void Handler<Storage, Logger>::drop(const time_type time)
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
    time_type fstCmdTime;

    for(std::string line; std::getline(istream, line);)
    {
        if (isBulkStart_)
            fstCmdTime = std::chrono::steady_clock::now();

        if (line == smbl_[2])
        {
            if (!isDynamicBlock)
                drop(fstCmdTime);
            break;
        }
        else if (line == smbl_[0])
        {
            openBracketsCount++;
            if (openBracketsCount == 1)
            {
                isDynamicBlock = true;
                drop(fstCmdTime);
            }
            continue;
        }
        else if ((line == smbl_[1]) && (openBracketsCount > 0))
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