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
    using StoragePtr = std::shared_ptr<Storage>;
    using Loggers = std::vector<std::shared_ptr<Logger>>;
    using time_type = std::chrono::time_point<std::chrono::steady_clock>;

    StoragePtr storage_;
    int staticBlockSize_;
    Loggers loggers_;

    std::array<std::string, 3> smbl_;
    int staticBlockSizeCurrent_;
    bool isBulkStart_;

public:
    Handler(StoragePtr storage,
            const int staticBlockSize,
            const Loggers & loggers = {},
            const std::array<std::string, 3> smbl = {"{", "}", "EOF"})
    : storage_(storage)
    , staticBlockSize_(staticBlockSize)
    , loggers_(loggers)
    , smbl_(smbl)
    , staticBlockSizeCurrent_(staticBlockSize)
    , isBulkStart_(true)
    {}

    void read(std::istream& istream);

private:
    void drop(const time_type time);
};


template <typename Storage, typename Logger>
void Handler<Storage, Logger>::drop(const time_type time)
{
    storage_->setTime(time);

    for (auto& logger : loggers_)
        logger->write(*storage_);

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