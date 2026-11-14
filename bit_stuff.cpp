
#include <iostream>
#include <string>
using namespace std;

void bitStuffSender(string data, string &stuffed)
{
    int ones = 0;

    for(int i = 0; i < data.length(); i++)
    {
        stuffed += data[i];

        if(data[i] == '1')
        {
            ones++;

            if(ones == 5)
            {
                stuffed += '0';
                ones = 0;
            }
        }
        else
        {
            ones = 0;
        }
    }
}

void bitStuffReceiver(string stuffed, string &original)
{
    int ones = 0;

    for(int i = 0; i < stuffed.length(); i++)
    {
        original += stuffed[i];

        if(stuffed[i] == '1')
        {
            ones++;

            if(ones == 5)
            {
                i++; // Skip stuffed 0
                ones = 0;
            }
        }
        else
        {
            ones = 0;
        }
    }
}

void addFrame(string data, string &frame)
{
    string FLAG = "01111110";
    string stuffed = "";

    bitStuffSender(data, stuffed);

    frame = FLAG + stuffed + FLAG;
}

void removeFrame(string frame, string &data)
{
    string FLAG = "01111110";

    if(frame.length() < 16 ||
       frame.substr(0, 8) != FLAG ||
       frame.substr(frame.length() - 8) != FLAG)
    {
        cout << "Invalid Frame!";
        return;
    }

    string stuffed = frame.substr(8, frame.length() - 16);

    bitStuffReceiver(stuffed, data);
}

int main()
{
    string data, frame, received = "";

    cout << "Enter data: ";
    cin >> data;

    addFrame(data, frame);

    cout << "\nTransmitted Frame: " << frame;

    removeFrame(frame, received);

    cout << "\nReceived Data: " << received;

    return 0;
}
