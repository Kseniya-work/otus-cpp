#pragma once

#include <iostream>
#include <string>
#include <vector>


class Handler
{
private:
    int staticBlockSize_;
    bool isDynamicBlockStarted_;
    int openBracketsCount_;
    std::vector<std::string> buffer_;

public:
    Handler(const int staticBlockSize)
    : staticBlockSize_(staticBlockSize)
    , isDynamicBlockStarted_(false)
    , openBracketsCount_(0)
    , buffer_()
    {}

    void write(std::istream& istream);
    void print() const;

};
