#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <stdio.h>

#include "com_client.hpp"
#include <lsl_cpp.h>


int
main(int argc, char **argv)
{
    if(argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " path"
                  << std::endl;
        exit(0);
    }
    std::string path = argv[1];
    int port = -1;
    std::cout << "Com Interface:" << std::endl;
    Communication::Client device(true);
    try
    {
            device.open_connection(Communication::Client::SERIAL, path.c_str());
    }
    catch(std::string msg)
    {
        std::cout << "ERROR: " << msg << "\n";
        return 0;
    }


    try
    {
        usleep(2000000);
        int nb_ch = 8+6;
        lsl::stream_info info_sample("loadcells", "sample", nb_ch, 0,
                                     lsl::cf_int32);
        lsl::stream_outlet outlet_sample(info_sample);
        std::vector<int32_t> sample(nb_ch);
        std::cout << "[INFOS] Now sending data... " << std::endl;
        for(int t = 0;; t++)
        {
            uint8_t buff[24] = {'1'};
            int a = device.writeS(buff, 1);
            std::cout << a << std::flush;
            int tot = 32;

            std::cout << " ... ";
            int n = device.readS(buff, tot, false);

            std::cout << n << std::endl;
            for(uint8_t i = 0; i < 8; i++)
            {
                sample[i] = ((int32_t *)(buff))[i];
                std::cout << sample[i] << " ";
            }
            //regress(sample);//get the Force/Torque value from the 8 load cells value via a meansquare linearisation.
            
            std::cout << std::endl;
            outlet_sample.push_sample(sample);
        }
    }
    catch(std::exception &e)
    {
        std::cerr << "[ERROR] Got an exception: " << e.what() << std::endl;
    }
    uint8_t b[1] = {'n'};
    device.writeS(b, 1);

    return 0; // success
}
