# Tobii 4C for linux
This repository was created in order to make the Tobii 4C eye tracker compliant with **Systemd**, the modern and most used system initializer among linux distributions. 



### Why another 4C installer?

As you may already know, [@Eitol](https://github.com/Eitol) kindly provided a [suite](https://github.com/Eitol/tobii_eye_tracker_linux_installer) of scripts for installing and testing the 4C on Ubuntu-like systems, but unfortunately it does not work on my distro (Archlinux), mainly because some of these scripts still rely on **SysVinit**, which has been deprecated in most modern distros. 



### Installing / uninstalling

Run the `install.sh` script int the root folder for a system-wide installation of all required services. Please check wether the paths contained in the script match your own (your are doing this at your own risk):

```
chmod u+x install.sh
./install.sh
```

To uninstall Tobii 4C tools and services (again, check the paths beforehand):

```
chmod u+x uninstall.sh
./uninstall.sh
```



### Examples

There are two examples for testing the installation. One was provided by [@Eitol](), which is available in the subfolder `test`. The other one is a “streamer” app that keeps updating the eye gaze position via UDP sockets at `127.0.0.1:9998`, and your can find it in `streamer`. Assuming you have cmake, you could do the following:

```
cd examples/test
mkdir build && cd build
cmake ..
make
./example
```



##### Disclaimer

I don’t have any relationship with Tobii and I don’t own the libraries and the tools provided here. They have been made [publicly available](https://developer.tobii.com/community/forums/topic/tobii-4c-eye-tracker-on-linux/) by Tobii and you should check with them about license.



##### Acknowledgments

Special thanks to [@Eitol](https://github.com/Eitol) for putting together all the necessary tools from Tobii.

