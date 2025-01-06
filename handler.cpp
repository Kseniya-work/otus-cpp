#include "handler.h"

void Handler::print() const
{
    std::cout << "bulk: ";
    for (auto it = buffer_.begin(); it != buffer_.end(); it++)
    {
        std::cout << (it != buffer_.begin() ? ", " : "") << *it;
    }
    std::cout << std::endl;
}

void Handler::write(std::istream& istream)
{
    int staticBlockSizeCurrent = staticBlockSize_;
    for(std::string line; std::getline(istream, line);)
    {
        if (line == "{")
        {
            openBracketsCount_++;
            isDynamicBlockStarted_ = true;
        }
        else if (line == "}" && openBracketsCount_ > 0)
        {
            openBracketsCount_--;
            if (openBracketsCount_ == 0)
                isDynamicBlockStarted_ = false;
        }
        else if (line == "EOF")
        {
            if (!isDynamicBlockStarted_)
            {
                print();
            }
            break;
        }

        staticBlockSizeCurrent--;
        if (staticBlockSizeCurrent < 0)
        {
            staticBlockSizeCurrent = staticBlockSize_ - 1;
            print();
            buffer_.clear();
        }

        buffer_.emplace_back(line);
    }
}