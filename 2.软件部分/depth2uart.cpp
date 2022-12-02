#include <boost/asio.hpp>       // for uart send and data
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <iostream>             // for cout
#include <unistd.h>

using namespace std;
using namespace boost::asio;

boost::asio::io_service iosev;
boost::asio::serial_port sp(iosev);
boost::system::error_code err;

const unsigned char ender[2] = {0x0d, 0x0a};        // Data ender
const unsigned char header[2] = {0x55, 0xaa};       // Data header

void serialInit()
{
    sp.open("/dev/ttyUSB0", err);
    if(err){
        std::cout << "Error: " << err << std::endl;
        std::cout << "Check your uart /dev/ttyUSB0 \n 1.Check whether the serial port read/write permission is enabled \n 2.Check if the serial port name is correct" << std::endl;
        return ;
    }
    sp.set_option(serial_port::baud_rate(115200));
    sp.set_option(serial_port::flow_control(serial_port::flow_control::none));
    sp.set_option(serial_port::parity(serial_port::parity::none));
    sp.set_option(serial_port::stop_bits(serial_port::stop_bits::one));
    sp.set_option(serial_port::character_size(8));    

    iosev.run();
}

void WriteData(double Depth_center)
{
    unsigned char buf[6] = {0};
    int i;

    // Set data header
    for(i = 0; i < 2; i++)
        buf[i] = header[i];             //buf[0]  buf[1]
    
    buf[2] = Depth_center/256;          //depth=buf[2]*256+buf[3]
    buf[3] = Depth_center;

    // Set data ender
    for(i = 0; i < 2; i++)
        buf[4+i] = ender[i];

    // Send data
    boost::asio::write(sp, boost::asio::buffer(buf));
}

int main(int argc, char * argv[]) try
{
    // Create a Pipeline
    rs2::pipeline p;

    // Configure and start the pipeline
    p.start();

    serialInit();

    while (true)
    {
        // Block program until frames arrive
        rs2::frameset frames = p.wait_for_frames();

        // Try to get a frame of a depth image
        rs2::depth_frame depth = frames.get_depth_frame();

        // Get the depth frame's dimensions
        auto width = depth.get_width();
        auto height = depth.get_height();

        // Query the distance from the camera to the object in the center of the image
        double dist_to_center = depth.get_distance(width / 2, height / 2);

        // m to mm
        dist_to_center *= 1000;

        // Send/Print the distance data
        WriteData(dist_to_center);
        // std::cout << "The camera is facing an object " << dist_to_center << " millimeters away \r";
    }

    return EXIT_SUCCESS;
}

catch (const rs2::error & e)
{
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
    return EXIT_FAILURE;
}

catch (const std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}
