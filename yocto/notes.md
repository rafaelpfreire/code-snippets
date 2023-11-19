Four elements of embedded Linux
--------------------------------

- Toolchain: The compiler and other tools needed to create code for your target device. Everything else depends on the toolchain.
- Bootloader: The program that initializes the board and loads the Linux kernel.
- Kernel: This is the heart of the system, managing system resources and interfacing with hardware.
- Root filesystem: Contains the libraries and programs that are run once the kernel has completed its initialization.
One more element can be collection of programs specific to your embedded application which make the device do whatever it is supposed to do, be it weigh groceries, display movies, control a robot, or fly a drone.

What is Yocto?
----------------

Yocto is the smallest SI metric system prefix

Like 'm' stands for milli ( 10^-3 ).

So is yocto ( y = 10^-24 )

Poky includes 
	some OE components(oe-core)
	bitbake
	demo-BSP's
	helper scripts to setup environment
	emulator QEMU to test the image

Workflow of Yocto Project
===========================

Step 1: Download the Poky Source code

$ git clone git://git.yoctoproject.org/poky

Step 2: Checkout the latest branch/release (zeus)

$ git checkout zeus

Step 3: Prepare the build environment

Poky provides you a script 'oe-init-build-env', which should be used to setup the build environment

script will set up your environment to use Yocto build system,including adding the BitBake utility to your path

$ source poky/oe-init-build-env [ build_directory ]

Here build_directory is an optional argument for the name of the directory where the environment is set

in case it is not given , it defaults to "build"

The above script will move you in a build folder and create two files ( local.conf, bblayers.conf ) inside conf folder

Step 4: Building Linux Distribution

$ bitbake <image_name>
$ time bitbake core-image-minimal

You can also install the toolchain sdk in order to debug and test new applications
$ bitbake petalinx-image-minimal -c populate_sdk
The toolchain installer script will be located at build/tmp/deploy/sdk

core-image-minimal
----------------------

This is a small image allowing a device to boot, and it is very useful for kernel and boot loader tests and development

Command to run the generated image in QEMU
==========================================

Quick Emulator ( QEMU ) is a free and open source software package that performs hardware virtualization.
The QEMU based machines allow test and development without real hardware. Currently emulations are supported for:
        • ARM
        • MIPS
        • MIPS64
        • PowerPC
        • X86
        • X86_64


Poky provides a script 'runqemu' which will allow you to start the QEMU using yocto generated images.
The runqemu script is run as:
   runqemu <machine> <zimage> <filesystem>

where:
   <machine> is the machine/architecture to use (qemuarm/qemumips/qemuppc/qemux86/qemux86-64)
   <zimage> is the path to a kernel (e.g. zimage-qemuarm.bin)
   <filesystem> is the path to an ext2 image (e.g. filesystem-qemuarm.ext2) or an nfs directory

Full usage instructions can be seen by running the command with no options specified.

Exit QEMU
-----------

Exit QEMU by either clicking on the shutdown icon or by typing Ctrl-C in the QEMU transcript window from which you evoked QEMU.

Steps to generate ARM image and run in QEMU
==========================================

When you set up the build environment, a local configuration file named local.conf becomes available in a conf subdirectory of the Build Directory
The defaults are set to build for a qemux86-64 target

Edit ./build/conf/local.conf

Set

MACHINE = "qemuarm"

$ source poky/oe-init-build-env

$ bitbake core-image-minimal

$ runqemu core-image-minimal

Nographic
-----------

You can launch QEMU without the graphic window by adding nographic to the command line
$ runqemu qemuarm nographic

To add a particular package in your root file system
===================================================

Open your local.conf file and add the recipe name below

IMAGE_INSTALL += "recipe-name"

E.g. IMAGE_INSTALL += "usbutils" for lsusb

or IMAGE_INSTALL_append = " usbutils"

core-image-sato
----------------

This is the X11 Window-system-based image with a SATO theme and a GNOME mobile desktop environment

$ bitbake core-image-sato

Challenge
--------------

What changes you make to generate an image for qemu mips?
Once generated run the image in qemu emulator

Setting up Build Machine
--------------------------

Prerequisites
----------------

1. 50 Gbytes of free disk space

2. Runs a supported Linux distribution (i.e. recent releases of Fedora, openSUSE, CentOS, Debian, or Ubuntu). 

3. 
	Git 1.8.3.1 or greater

	tar 1.27 or greater

	Python 3.4.0 or greater.

Packages and package installation vary depending on your development system.

(*) Install the required packages for Yocto to Work from https://docs.yoctoproject.org/ref-manual/system-requirements.html

$ sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
    build-essential chrpath socat cpio python python3 python3-pip python3-pexpect \
    xz-utils debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev \
    pylint3 xterm


Poky
-----------

Poky is a reference distribution of Yocto Project. The word "reference" is used to mean "example" in this context.

Yocto Project uses Poky to build images (kernel, system, and application software) for targeted hardware.

At the technical level it is a combined repository of the components
	• Bitbake
	• OpenEmbedded Core
	• meta-yocto-bsp
	• Documentation

Note: Poky does not contain binary files,it is a working example of how to build your own custom Linux distribution from source.

What is difference between poky and Yocto
-----------------------------------------

The exact difference between Yocto and Poky is Yocto refers to the organization ( like one would refer to 'canonical', the company behind Ubuntu ), and Poky refers to the actual bits downloaded ( analogous to 'Ubuntu' )

Metadata 
-------------

Non Yocto:  A set of data that describes and gives information about other data

Yocto World: 
	Metadata refers to the build instructions
	Commands and data used to indicate what versions of software are used
	Where they are obtained from
	Changes or additions to the software itself ( patches ) which are used to fix bugs or customize the software for use in a particular situation

Metadata is collection of
	• Configuration files (.conf)
	• Recipes (.bb and .bbappend)
	• Classes (.bbclass)
	• Includes (.inc)

OpenEmbedded Project
-----------------------

From http://www.openembedded.org/wiki/Main_Page

OpenEmbedded offers a best-in-class cross-compile environment. It allows developers to create a complete Linux Distribution for embedded systems.

What is the difference between OpenEmbedded and the Yocto Project?
------------------------------------------------------------------

The Yocto Project and OpenEmbedded share a core collection of metadata called openembedded-core. 

However, the two organizations remain separate, each with its own focus

OpenEmbedded provides a comprehensive set of metadata for a wide variety of architectures, features, and applications

	Not a reference distribution
	Designed to be the foundation for others

The Yocto Project focuses on providing powerful, easy-to-use, interoperable, well-tested tools, metadata, and board support packages (BSPs) for a core set of architectures and specific boards.


OpenEmbedded-Core(oe-core)
---------------------------

The Yocto Project and OpenEmbedded have agreed to work together and share a common core set of metadata(recipes, classes and associated files): oe-core


Bitbake
-----------

Bitbake is a core component of the Yocto Project.

It basically performs the same functionality as of make.

It's a task scheduler that parses python and shell script mixed code

The code parsed generates and runs tasks, which are basically a set of steps ordered according to code's dependencies.

It reads recipes and follows them by fetching packages, building them and incorporating the results into bootable images.

It keeps track of all tasks being processed in order to ensure completion, maximizing the use of processing resources to reduce build time and being predictable.

meta-yocto-bsp
----------------

A Board Support Package (BSP) is a collection of information that defines how to support a particular hardware device, set of devices, or hardware platform

The BSP includes information about the hardware features present on the device and kernel configuration information along with any additional hardware drivers required.

The BSP also lists any additional software components required in addition to a generic Linux software stack for both essential and optional platform features.

The meta-yocto-bsp layer in Poky maintains several BSPs such as the Beaglebone, EdgeRouter, and generic versions of both 32-bit and 64-bit IA machines.

Machines supported
-------------------
Texas Instruments BeagleBone (beaglebone)
Freescale MPC8315E-RDB (mpc8315e-rdb)
Intel x86-based PCs and devices (genericx86 and genericx86-64)
Ubiquiti Networks EdgeRouter Lite (edgerouter)

Note: To develop on different hardware, you will need to complement Poky with hardware-specific Yocto layers.

Metadata
--------------

Poky = Bitbake + Metadata

Metadata is collection of
	• Configuration files (.conf)
	• Recipes (.bb and .bbappend)
	• Classes (.bbclass)
	• Includes (.inc)

Recipes
---------

Non-Yocto: A recipe is a set of instructions that describe how to prepare or make something, especially a dish

Yocto: A recipe is a set of instructions that is read and processed by the bitbake

Extension of Recipe: .bb

A recipe describes:
    where you get source code
    which patches to apply
    Configuration options
    Compile options (library dependencies)
    Install
    License

a software component

Examples of Recipes
----------------------

dhcp_4.4.1.bb
gstreamer1.0_1.16.1.bb

Configuration Files
--------------------

Files which hold
    global definition of variables
    user defined variables and
    hardware configuration information

They tell the build system what to build and put into the image to support a particular platform

Extension: .conf

Types
--------

	• Machine Configuration Options
	• Distribution Configuration Options
	• Compiler tuning options
	• General Common Configuration Options
	• User Configuration Options (local.conf)


classes
---------

Class files are used to abstract common functionality and share it amongst multiple recipe (.bb) files

To use a class file, you simply make sure the recipe inherits the class

Eg. inherit classname

Extension: .bbclass

They are usually placed in classes directory inside the meta* directory

Example of classes
-------------------

cmake.bbclass - Handles cmake in recipes
kernel.bbclass - Handles building kernels. Contains code to build all kernel trees
module.bbclass - Provides support for building out-of-tree Linux Kernel Modules

Layers
--------

A collection of related recipes.

or

Layers are recipe containers (folders)

Typical naming convention: meta-<layername>

Poky has the following layers:

meta, meta-poky, meta-selftest, meta-skeleton, meta-yocto-bsp

Why Layers
-----------

Layers provide a mechanism to isolate meta data according to functionality, for instance BSPs, distribution configuration, etc.

You could have a BSP layer, a GUI layer, a distro configuration, middleware, or an application

Putting your entire build into one layer limits and complicates future customization and reuse. 

Example: meta-poky          -- Distro metadata
         meta-yocto-bsp     -- BSP    metadata

Layers allow to easily to add entire sets of meta data and/or replace sets with other sets.
meta-poky, is itself a layer applied on top of the OE-Core metadata layer, meta

Layers
----------

Which layers are used by Poky build system?
-------------------------------------------

BBLAYERS variable present in build/conf/bblayers.conf file list the layers Bitbake tries to find

If bblayers.conf is not present when you start the build, the OpenEmbedded build system creates it from bblayers.conf.sample when you source the oe-init-build-env script

Command to find out which layers are present
----------------------------------------------

$ bitbake-layers show-layers

Note: You can include any number of available layers from the Yocto Project 

Where to get other layers
--------------------------

https://layers.openembedded.org/layerindex/branch/master/layers/

Yocto Project Compatible Layers
--------------------------------

https://www.yoctoproject.org/software-overview/layers/

These layers are tested and are fully compatible with yocto project.

OpenEmbedded layer index contains more layers but the content is less universally validated

Image
-----------

An image is the top level recipe, it has a description, a license and inherits the core-image class

It is used alongside the machine definition

machine describes the hardware used and its capabilities

image is architecture agnostic and defines how the root filesystem is built, with what packages.

By default, several images are provided in Poky

Command to check the list of available image recipes
----------------------------------------------------

$ ls meta*/recipes*/images/*.bb

Packages
-------------

Non-Yocto: Any wrapped or boxed object or group of objects.

Yocto: A package is a binary file with name *.rpm, *.deb, or *.ipkg

A single recipe produces many packages. All packages that a recipe generated are listed in the recipe variable


$ vi  meta/recipes-multimedia/libtiff/tiff_4.0.10.bb
PACKAGES =+ "tiffxx tiff-utils"

Poky source tree
------------------

bitbake		-	Holds all Python scripts used by the bitbake command
			bitbake/bin is placed into the PATH environmental variable so bitbake can be found

documentation   -       All documentation sources for the Yocto Project documentation
			Can be used to generate nice PDFs

meta		-	Contains the oe-core metadata
			
meta-poky	-	Holds the configuration for the Poky reference distribution
			local.conf.sample, bblayers.conf.sample are present here

meta-skeleton	- 	Contains template recipes for BSP and kernel development


meta-yocto-bsp  -	Maintains several BSPs such as the Beaglebone, EdgeRouter, 
			and generic versions of both 32-bit and 64-bit IA machines.

scripts		-	Contains scripts used to set up the environment, development tools,
			and tools to flash the generated images on the target.

LICENSE		-	The license under which Poky is distributed (a mix of GPLv2 and MIT).
Where should i place the content of conf/local.conf as this file is part of build folder?
------------------------------------------------------------------------------------------

In general, everything in your local.conf should be moved to your own distro configuration

Finally, you should only set DISTRO to your own distro in local.conf
conf
-----------

When you run source poky/oe-init-build-env, it will create a "build" folder in that directory
Inside this build folder, it will create "conf" folder which contains two files:

1. local.conf
2. bblayers.conf

local.conf
-------------

Configures almost every aspect of the build system
Contains local user settings

MACHINE: The machine the target is built for
	Eg: MACHINE = "qemux86-64"

DL_DIR: Where to place downloads
	During a first build the system will download many different source code tarballs,from various 
	upstream projects.These are all stored in DL_DIR
	The default is a downloads directory under TOPDIR which is the build directory

TMP_DIR:  Where to place the build output
	  This option specifies where the bulk of the building work should be done and
	  where BitBake should place its temporary files(source extraction, compilation) and output

Important Point:
----------------

local.conf file is a very convenient way to override several default configurations over all the Yocto Project's tools.

Essentially, we can change or set any variable, for example, add additional packages to an image file

Though it is convenient, it should be considered as a temporary change as the build/conf/local.conf file is not usually tracked by any source code management system.	

bblayers.conf
------------------

The bblayers.conf file tells BitBake what layers you want considered during the build.

By default, the layers listed in this file include layers minimally needed by the build system

However, you must manually add any custom layers you have created

E.g: BBLAYERS = "\
                                  /home/linuxtrainer/poky/meta \
                                 /home/linuxtrainer/poky/meta-poky \
                                 /home/linuxtrainer/poky/meta-yocto-bsp \
                                 /home/linuxtrainer/poky/meta-mylayer \
                                 "
This example enables four layers, one of which is a custom user defined layer named "meta-mylayer"

BB_NUMBER_THREADS
-----------------

	Determines the number of tasks that Bitbake will perform in parallel
	Note: These tasks are related to bitbake and nothing related to compiling
	Defaults to the number of CPUs on the system
	$ bitbake -e core-image-minimal | grep ^BB_NUMBER_THREADS=


PARALLEL_MAKE
--------------

	Corresponds to the -j make option
	specifies the number of processes that GNU make can run in parallel on a compilation task
	Defaults to the number of CPUs on the system
	$ bitbake -e core-image-minimal | grep ^PARALLEL_MAKE=

Where should i place the content of conf/local.conf as this file is part of build folder?
------------------------------------------------------------------------------------------
Other directories
-----------------

downloads	-	downloaded upstream tarballs/git repositories of the recipes used in the build

sstate-cache	-	shared state cache

tmp		-	Holds all the build system output

			tmp/deploy/images/machine - Images are present here
			
cache		-	cache used by the bitbake's parser
Yocto/OpenEmbedded Build System Workflow
-----------------------------------------

1. Developers specify architecture, policies, patches and configuration details.

2. The build system fetches and downloads the source code from the specified location
	supports downloading tarballs and source code repositories systems such as git/svn

3. extracts the sources into a local work area

4. patches are applied

5. steps for configuring and compiling the software are run

6. installs the software into a temporary staging area
	depending on the user configuration, deb/rpm/ipk binaries are generated

7. the build system generates a binary package feed that is used to create the final root file image.

8. finally generates the file system image and a customized Extensible SDK (eSDK) for application development in parallel

Images generated by Poky Build
---------------------------------

The build process writes images out to the Build Directory inside the tmp/deploy/images/machine/ folder

1. kernel-image: 
		A kernel binary file
		The KERNEL_IMAGETYPE variable determines the naming scheme for the kernel image file.
		$ bitbake -e core-image-minimal | grep ^KERNEL_IMAGETYPE=

2. root-filesystem-image: 
		Root filesystems for the target device (e.g. *.ext3 or *.bz2 files).
		The IMAGE_FSTYPES variable determines the root filesystem image type
		$ bitbake -e core-image-minimal | grep ^IMAGE_FSTYPES=

3. kernel-modules:
		Tarballs that contain all the modules built for the kernel

4. bootloaders:
		If applicable to the target machine, bootloaders supporting the image.

symlinks
-----------
	symbolic link pointing to the most recently built file for each machine
	These links might be useful for external scripts that need to obtain  latest version of each file

Saving Disk Space while building Yocto 
=====================================

Yocto Build System can take a lot of disk space during build. But bitbake provides options to preserve disk space

You can tell bitbake to delete all the source code, build files after building a particular recipe by adding the following line in local.conf file

INHERIT += "rm_work"

Disadvantage: Difficult to debug while build fails of any recipe.

For example, if you want to exclude bitbake deleting source code of a particular package, you can add it in RM_WORK_EXCLUDE += "recipe-name"

E.g: RM_WORK_EXCLUDE += "core-image-minimal"

What is the difference between ipkg/deb/rpm etc?

Yocto Project Releases
------------------------

Naming Convention
-----------------

Yocto Project releases follow the naming convention: Major.Minor.patch number

Eg. yocto-2.7.3

Major release number changes imply compatibility changes with previous releases

Minor release number changes imply significant changes up to, but not including compatibility changes

Minor rev number changes are for minor issues such as simple bugfixes, security updates, etc.

Poky Releases
--------------

Poky releases has code names as well as Major.Minor.patch numbering

Yocto Project/Poky Release, are released at the same time
Yocto Project Releases
-----------------------

Major Releases: Every six months in April and October

Minor Releases: 
	No Particular schedule
	Driven by the accumulation of enough significant fixes or enhancements to the associated major release

Concept of codenames
---------------------

Branches of metadata with the same codename are compatible with each other
Types of Releases
--------------------

a) Milestone Releases
----------------------

Major Release is divided into milestone releases.

Milestone releases are used as:

	checkpoints for our progress

	preview for the public community

	to manage changes in the middle of a release 

Each milestone lasts about 4-8 weeks and has one planning week, several development weeks, stabilization weeks and one release week:

b) Point Releases
-------------------

A point release is a minor release such as 1.0.x

Point releases are necessary to address the following:

	Issues building on current Linux distributions.
	fix critical bugs and security issues (CVEs) for the first 6 months after release
	fix security issues for the first year after release

Release Lifecycle
----------------------

There are two possible lifecycles a release may follow:

Initial Release -> Stable -> Community -> EOL

	OR

Initial Release -> LTS	-> Community  -> EOL

Stable vs LTS Release Difference
---------------------------------

Stable releases are maintained for seven months

LTS releases are maintained initially for two years

LTS releases are preannounced and known to be LTS in advance (usually every two years)

Community Support
-------------------

Branch transitions to community support after the last stable dot release identified by the stable/LTS maintainer.

A call for a community support maintainer is sent to the mailing lists.
	A six (6) week waiting period.
	if there is no new maintainer, then the branch goes to into EOL status


Note:	Branches only have community support status if there is an active community member willing to step into the maintainer role for that series
Layers and Branches
---------------------

Layers being developed simultaneously by several different parties, the different flavors of Yocto and subsequent layers have to be split into branches in Git

Most BSP layers will only work with OpenEmbedded-Core of the same branch.

Mixing branches among your layers will end up in conflicts

For example, the so called bbappends, sometimes are tied to specific version number and will break the build if those versions are not found in the layers.

Which Branch to choose?
-------------------------

You should evaluate all the layers and find a compromise between:

    Getting the latest stable branch
    Getting the latest branch supported by all layers.

Note:  yocto branch you decided to use, could not be supported by your current host linux distribution.
Eg:  I want to use a layer which forces me to stick with Krogoth, but this branch is not tested with newer distributions such as Ubunutu 16.04 or 18.04.

What is BSP Layer?
-------------------

A collection of information(metadata) that defines how to support 
	a particular hardware device, 
	set of devices, or 
	hardware platform
What is BSP Layer?
-------------------
BSP Layer
----------

Naming Convention: meta-<bsp_name>

How to find out what all hardware devices are supported
---------------------------------------------------------

conf/machine/*.conf list all the hardware devices supported by the BSP layer
meta-ti
----------

BSP Layer for Texas Instrument Hardware

$ cd sources

$ git clone git://git.yoctoproject.org/meta-ti

Hardware Configuration Supported
----------------------------------

a) Beagle Bone Black

b) Beagle Board

c) Panda Board

d) OMAP boards
meta-ti vs meta-yocto-bsp
--------------------------

meta-yocto-bsp:
---------------

    provides "reference" BSPs for each of the supported architectures
    One for ARM (BeagleBone Black), one for MIPS, PPC and x86.
    it is based on the mainline kernel/bootloader
    does not support any advanced features or anything not in the upstream mainline kernel
    e.g. no capes, no power management, no hardware acceleration, no 3D, no PRU, etc.
    The purpose of this BSP is to have some basic out-of-box experience for the select hardware platforms within Poky to evaluate the Yocto Project and OpenEmbedded framework, but not the specific hardware platforms

meta-ti
----------

    official Texas Instruments BSP that provides the latest WIP "staging" kernel and bootloader
    most of the advanced features and peripheral support for the wider range of latest TI platforms

Adding Layers
--------------

Two ways:

1. Manual: edit bblayers.conf file and add the new layer to BBLAYERS
2. Automatic: 

$ bitbake-layers add-layer <path-to-new-layer>

$ bitbake-layers add-layer ~/Yocto_Training/source/meta-ti/
Steps for building
-------------------

Step1 : Source the environment script

	$ source poky/oe-init-build-env

	Add the meta-ti layer

	$ bitbake-layers add-layer ~/Yocto_Training/source/meta-ti/

Step2 : Open local.conf and set Machine to beaglebone
	MACHINE='beaglebone'

Step3 : Also add INHERIT += "rm_work" to save disk space

Step4 : Generate an minimal image

	$ bitbake core-image-minimal

Step5 : Once the build finished, you will find the output images under $BUILDDIR/tmp/deploy/images/beaglebone  
Flashing the image on the SD Card using wic
--------------------------------------------

wic images are SD Card images and can be directly written into sd-card

core-image-minimal-beaglebone.wic.xz is compressed wic image.

It can be uncompressed using the unxz utility

$ unxz core-image-minimal-beaglebone.wic.xz

$ ls -lh core-image-minimal-beaglebone.wic

Flash it to the sd card

$ lsblk

$ sudo dd if=core-image-minimal-beaglebone.wic of=/dev/sdb bs=4096 status=progress && sync




Challenge
---------------

Generate an image for beaglebone using meta-ti, but remove meta-yocto-bsp layer
Raspberry Pi 3
------------------
SoC: Broadcom BCM2837
CPU: 4× ARM Cortex-A53, 1.2GHz
GPU: Broadcom VideoCore IV
RAM: 1GB LPDDR2 (900 MHz)
Networking: 10/100 Ethernet, 2.4GHz 802.11n wireless
Bluetooth: Bluetooth 4.1 Classic, Bluetooth Low Energy
Storage: microSD
GPIO: 40-pin header
Ports: HDMI, 3.5mm analogue audio-video jack, 4× USB 2.0, Ethernet, Camera Serial Interface (CSI), Display Serial Interface (DSI)

Raspberry Pi Zero W and Yocto
------------------------------

	1GHz, Single-core CPU
	512MB RAM
	Mini HDMI and USB On-The-Go ports
	Micro USB power
	HAT-compatible 40-pin header
	Composite video and reset headers
	CSI camera connector
	802.11n wireless LAN
	Bluetooth 4.0

Steps for generating Yocto Image
----------------------------------

Everything is same except MACHINE = 'raspberrypi0-wifi'
Remotely access raspberry pi3
===============================

$ bitbake rpi-basic-image

dropbear is a SSH 2 server designed to be small enough to be used in small memory environments
IMAGE_ROOTFS_EXTRA_SPACE
------------------------

Adds extra free space to the root filesystem image.

The variable specifies the value in kilobytes

Default value : 0

For example, to add an additional 4 GB of space, set the variable to IMAGE_ROOTFS_EXTRA_SPACE = "4194304"
meta-raspberrypi
------------------

Hardware specific BSP overlay for the RaspberryPi device.

The core BSP part of meta-raspberrypi should work with different OpenEmbedded/Yocto distributions and layer
stacks, such as:
	• Distro-less (only with OE-Core).
	• Angstrom.
	• Yocto/Poky

Hardware Supported
--------------------

Raspberry Pi
Raspberry Pi 2
Raspberry Pi 3
Raspberry Pi 4
Raspberry Zero
Raspberry Zero Wireless

Link: git://git.yoctoproject.org/meta-raspberrypi

Dependencies
----------------

URI 	: git://git.openembedded.org/meta-openembedded
Layers	: meta-oe, meta-multimedia, meta-networking, meta-python
Steps to generate an Yocto Image for Raspberry Pi3
--------------------------------------------------

Poky has no support for Broadcom BCM SoC.

Step1: Download the BSP Layer for Raspberry Pi3

$ git clone git://git.yoctoproject.org/meta-raspberrypi

Step2: Download meta-openembedded branch as meta-raspberrypi layer depends upon it

$ git clone git://git.openembedded.org/meta-openembedded

Step3: Once you complete cloning, there should be three folders: poky, meta-openembedded, meta-raspberrypi

$ ls source

Step4: Run the environment script to setup the Yocto Environment and create build directory

$ source poky/oe-init-build-env build_pi

Step5: Add meta-openembedded layers ( meta-oe, meta-multimedia, meta-networking, meta-python) and meta-raspberrypi layer to bblayers.conf

Step6: Set the MACHINE in local.conf to "raspberrypi3".
$ echo 'MACHINE = "raspberrypi3"' >> conf/local.conf

Step7: Final step is to build the image. To find out the available images:
$ ls ../meta-raspberrypi/recipes-*/images/
Images
------------

rpi-hwup-image.bb: This is an image based on core-image-minimal

rpi-basic-image.bb: This is an image based on rpi-hwup-image.bb, with some added features (a splash screen)

rpi-test-image.bb: This is an image based on rpi-basic-image.bb, which includes some packages present in meta-raspberrypi

Enabling UART
--------------
RaspberryPi 3 does not have the UART enabled by default because this needs a fixed core frequency and enable_uart wil set it to the minimum

To enable it, set the following in local.conf

ENABLE_UART = "1"

$ bitbake rpi-hwup-image
Booting Process in Raspberry Pi3
---------------------------------

Broadcom BCM2837:
	CPU 	-	1.2GHz 64-bit quad-core ARMv8 Cortex-A53
	GPU 	-	Broadcom VideoCore IV
	SDRAM	-	1024 MiB

When you power the device
Stage 1 Booting - OnChip ROM
----------------------------
	GPU - On, CPU - Off, SDRAM - Off

	When the Pi is powered up the first thing that starts working is the GPU core and ARM CPU is held in reset

	The GPU core is the main part responsible for the first booting steps of the Pi. 

	Inside Broadcom’s SoC, there is a small boot ROM, its programmed by default to look for a file called
	bootcode.bin on the SD Card

	It loads bootcode.bin into L2 Cache memory		

Booting Process in Raspberry Pi3
---------------------------------

Stage 2 Booting - bootcode.bin
------------------------------

	GPU - On, CPU - Off, SDRAM - On

	Executed on VideoCore GPU
	Enables SDRAM
	Loads the third stage bootloader start.elf into SDRAM

Stage 3 Booting - start.elf
----------------------------

	GPU - On, CPU - On, SDRAM - On

	start.elf is actually a full fledge proprietary operating system for GPU known as VCOS (VideoCore OS).
	It starts by reading config.txt  which contains configuration parameters for
		VideoCore (Video/HDMI modes, memory, console frame buffers etc) and
		Linux Kernel (load addresses, device tree, uart/console baud rates etc)
		kernel = kernel7.img
	It also loads a file cmdline.txt if it exists, and will pass its contents as kernel command line
	Finally enables the ARM CPU and loads the kernel image which is executed on the ARM CPU
	It also loads the dtb file
		
Booting in Raspberry Pi3
---------------------------

GPU Core
first stage bootloader, which is stored in ROM on the SoC
bootcode.bin
start.elf
config.txt
cmdline.txt
kernel7.img

Flashing images on SD Card
-----------------------------

Images are present in tmp/deploy/images/raspberrypi3

$ lsblk

$ sudo dd if=rpi-hwup-image-raspberrypi3.rpi-sdimg of=/dev/sdb bs=4096 && sync
Hardware setup
================

An SD card with image flashed

Raspberry Pi 3

A power adapter that can supply 5V

USB TTL-2303(PL2303) for serial communication

USB-TTL is connected to the J8 connector of Raspberry Pi3 in the following formation:

J8 Pin           USB TTL Function
-------		-----------------
6                GND Ground

8                RXL

10               TXL

