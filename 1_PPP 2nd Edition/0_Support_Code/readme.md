# Support code for PPP 2nd Ed.
* Code provided by the Author of PPP2, Bjarne Stroustrup [Here!!](http://www.stroustrup.com/Programming/)
* For chap 12 to 16 (Graphics Part), I fixed up all header using this guide [Here!!](https://bumpyroadtocode.com/2017/08/05/how-to-install-and-use-fltk-1-3-4-in-visual-studio-2017-complete-guide/).
* For Visual Studio 2015 or up, We'll get WIN32 not defined error, just change it to _WIN32, because WIN32 is removed. I attached modified fltk library.
* For Visual Studio, we have to include this libraries to compile Graphics Part.


On debug mode
```
fltkd.lib
fltkjpegd.lib
fltkimagesd.lib
```
On Release mode
```
fltk.lib
fltkjpeg.lib
fltkimages.lib
```