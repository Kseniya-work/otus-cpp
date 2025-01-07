#pragma once

#include <iostream>
#include <string>
#include <vector>


class Handler
{
private:
    int staticBlockSize_;
    std::string endString_;
    std::string dynamicBlockBeginSymbol_;
    std::string dynamicBlockEndSymbol_;
    std::vector<std::string> buffer_;

public:
    Handler(const int staticBlockSize,
            const std::string endString = "EOF",
            const std::string dynamicBlockBeginSymbol = "{",
            const std::string dynamicBlockEndSymbol = "}")
    : staticBlockSize_(staticBlockSize)
    , endString_(endString)
    , dynamicBlockBeginSymbol_(dynamicBlockBeginSymbol)
    , dynamicBlockEndSymbol_(dynamicBlockEndSymbol)
    , buffer_()
    {}

    void write(std::istream& istream);
    void print() const;

};
