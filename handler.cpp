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
    static bool isDynamicBlockStarted = false;
    static int openBracketsCount = 0;
    int staticBlockSizeCurrent = staticBlockSize_;

    for(std::string line; std::getline(istream, line);)
    {
        if (line == endString_)
        {
            if (!isDynamicBlockStarted && !buffer_.empty())
                print();
            break;
        }
        else if (line == dynamicBlockBeginSymbol_)
        {
            openBracketsCount++;
            isDynamicBlockStarted = true;

            if ((openBracketsCount == 1) && !buffer_.empty())
            {
                print();
                buffer_.clear();
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
                buffer_.clear();
            }
            continue;
        }

        buffer_.emplace_back(line);
        if (!isDynamicBlockStarted && staticBlockSizeCurrent == 1)
        {
            print();
            buffer_.clear();
            staticBlockSizeCurrent = staticBlockSize_;
        }
        else if (!isDynamicBlockStarted && staticBlockSizeCurrent != 0)
        {
            staticBlockSizeCurrent--;
        }
    }
}