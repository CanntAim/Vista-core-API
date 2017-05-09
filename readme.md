<h1>Vista-Core-API</h1>
<h6><i><b>Warning:</b> This is a Legacy Project, I've released an update, but it may require tinkering to get working</i></h6>
<h2>Overview</h2>

<p> This was a computer vision project for real-time car counting in traffic. The design is fairly straight forward and the in-code documents should be fairly clear and extensive in how the program works. I'll provide a a quick visual high-level overview of what the program does below. I also have the demo file that I was using to test the application. The videos I was using to test it are not available here, obviously, but you can easily find your own if you want. Unfortuntely I don't have any unit-tests available for this application. I know, sue me.</p> 

<h2>What it does</h2>
<p>The specifications and requirements that this program met are listed below:</p>

* Count cars in traffic going in any given direction
* Capture and isolate the car image when it's counted for later analysis
* Record any other data that can be extracted immediately from the footage (extrapolating additional information was not in scope.)
* Multithreading (Multiple jobs can count cars along multiple paths at the same-time)
* Account for day and night cycles (changing light conditions)
* Account for stopped traffic
* Work in real-time
* Modular, can easily replace certain parts of the code.

<h2>Design</h2>
<p>This is a fairly general overview, primarily from memory:</p>

```
Car enters here!                                                      Cars exit here!
 _____________                                                        _____________
|             |                                                      |             |
|    Start    |            Direction of traffic                      |    End      |
|    Region   | ---------------------------------------------------> |    Region   |
|             |                                                      |             |
|_____________|                                                      |_____________|
       |_                                                                   _|
         |_                                                               _|
           |_                                                           _|
             |+---------------> Make entry in       Remove Entry <----+|
                                Transit Ledger   From Transit Ledger
                                      |                 |
                                      |                 |
                                  ____V_________________V____
                                 |                           |
                                 |  Car A -> Car B -> Car C  |
                                 |___________________________|
                                 
                                        
                                                |SUPPORTING UTLITIES|

                                Persistency/Missing Checker       Image Processors
                               |---------------------------|----------------------------|
                               | Subroutines keep tabs     | Subrountines that          |
                               | On the objects marked     | clean up images,           |           
                               | in the transit ledger     | do background subtraction, |                
                               | and maintains a notion    | histogram analysis, etc    |
                               | of continium across       |                            |
                               | consecutive frames        |                            |
                               |---------------------------|----------------------------|
                                   
```

<h2>Setup on Linux</h2>
<p>Simply follow the installation guide for OpenCV installation provided here:</p>
http://docs.opencv.org/3.0-last-rst/doc/tutorials/introduction/linux_install/linux_install.html
<p>Clone my repository to your local and proceed as followed:</p>

* Go to Vista-core-API and run:

```
mkdir _build
cd _build
cmake .. -DCMAKE_INSTALL_PREFIX=../_install
make
make install
```
* Go to Vista-cmd-example and re-run the above command. Note that you need to change to your own path here:

```
target_link_libraries(vista-example -lm -ldl -pthread ${OpenCV_LIBS} /home/vanya/Repos/vista/Vista-core-API/_install/lib/libvista-core.a -ldl)
```

<p>It should compile succesfully (I had some warnings using default flags, will try to get rid of them if I have time). I have included a proper cmake list files in the repository that you can use to generate a makefile and then run make. You can include the resulting binary as a dependency in another project. Or if you prefer you can include the source directly in your project and compile it using your own makefile.
