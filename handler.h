#pragma once

#include "storage.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

template <typename Storage>
class Handler
{
private:
    using StoragePtr = std::unique_ptr<Storage>;

    StoragePtr storage_;
    int staticBlockSize_;
    std::string endString_;
    std::string dynamicBlockBeginSymbol_;
    std::string dynamicBlockEndSymbol_;

public:
    Handler(StoragePtr storage,
            const int staticBlockSize,
            const std::string endString = "EOF",
            const std::string dynamicBlockBeginSymbol = "{",
            const std::string dynamicBlockEndSymbol = "}")
    : storage_(std::move(storage))
    , staticBlockSize_(staticBlockSize)
    , endString_(endString)
    , dynamicBlockBeginSymbol_(dynamicBlockBeginSymbol)
    , dynamicBlockEndSymbol_(dynamicBlockEndSymbol)
    {}

    void write(std::istream& istream);
    void print() const;
};


template <typename Storage>
void Handler<Storage>::print() const
{
    std::cout << "bulk: ";
    for (auto it = storage_->begin(); it != storage_->end(); ++(it))
    {
        std::cout << (it != storage_->begin() ? ", " : "") << *it;
    }
    std::cout << std::endl;
}

template <typename Storage>
void Handler<Storage>::write(std::istream& istream)
{
    static bool isDynamicBlockStarted = false;
    static int openBracketsCount = 0;
    int staticBlockSizeCurrent = staticBlockSize_;

    for(std::string line; std::getline(istream, line);)
    {
        if (line == endString_)
        {
            if (!isDynamicBlockStarted && !storage_->empty())
                print();
            break;
        }
        else if (line == dynamicBlockBeginSymbol_)
        {
            openBracketsCount++;
            isDynamicBlockStarted = true;

            if ((openBracketsCount == 1) && !storage_->empty())
            {
                print();
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
                print();
                storage_->clear();
            }
            continue;
        }

        storage_->add(line);
        if (!isDynamicBlockStarted && staticBlockSizeCurrent == 1)
        {
            print();
            storage_->clear();
            staticBlockSizeCurrent = staticBlockSize_;
        }
        else if (!isDynamicBlockStarted && staticBlockSizeCurrent != 0)
        {
            staticBlockSizeCurrent--;
        }
    }
}