# Introduction #
## What is Freasy? ##
Freasy is a easy to and use highly mobile system that enables mobile phone users to rapidly access a bunch of applications with a very little footprint on the local system. The idea is that the phone only has a tiny launcher program that then fetches a list of application, from which the user then select one to run.

Every program is developed with the MoSync SDK, which then can make the code runnable on a large number of platforms. Today, most cell phone developer have its own system for creating and then distributing applications for its own platforms. That is a problem, and it is solved with Freasy.

The whole Freasy system can be divided into three parts; a launcher of application, a application browser and a server.

The launcher is a program that uses the MoSync virtual machine, enabling it to launch other applications compiled in MoSyncs's IDE within itself. The launcher is the one piece of software that user only needs to have on its cell phone in order to run Freasy. The browser is used, as the names suggests, to browse for applications and is downloaded at startup.

When the launcher program is executed on a cell phone it first checks if the phone has a copy of the newest version of the browser. If it does not have the newest browser, or if it does not have one at all, it downloads the latest version of the browser from the server and then executes it. This, of course, requires a phone with that can connect to the Internet.

The browser is downloaded from the server and displays a number of applications, found with the help of a database, for the user to choose from. It displays not only the names of applications, but also lets you see other information about them. You can also search for applications, or select to show applications based on a given category of applications.

## What is MoSync? ##
MoSync AB is a company, previously known as Mobile Sorcery AB, that have developed a free platform for developing platform independent cell phone applications. The vision for MoSync is to make it easy, fast and cost efficient to develop and distribute mobile applications over a broad range of devices, platforms and distribution channels. The goal is to enable developers to spend the majority of their time and effort to develop the actual applications, and not re-coding them for other platforms.

The MoSync SDK is a cell phone software development kit based on common programming practices and standards, like full Eclipse integration and C/C++. With MoSync SDK you can easily develop complex applications and then, with a few clicks, build that application for many different mobile phone platforms and hundreds of different mobile phone devices.

![http://www.mosync.com/system/files/mosync-roadmap.jpg](http://www.mosync.com/system/files/mosync-roadmap.jpg)

## What is "free software"? ##
The Freasy system is composed out of free software. "Free software", as defined by the [Free Software Foundation](http://www.fsf.org/), is composed out of four essenstial freedoms for the users of the software have:

  * The freedom to run the program, for any purpose.
  * The freedom to study how the program works, and change it to make it do what you wish.
  * The freedom to redistribute copies so you can help your neighbor.
  * The freedom to distribute copies of your modified versions to others.

The word "free" in "free software" therfore referes to "freedom" and not "of no cost". Howerver, free software does not usually cost anything.

# Using Freasy #
## For the normal users ##
The normal user only have to download the Freasy launcher to get started. Depending on your cell phone you will need a differently compiled launcher. In the future there will be a service for device detection where you visit a site online, type your cell phone model and get a download link the right version which you then have to put into your cell phone.
However for the prototype we made, we have only compiled the launcher for the specific mobiles we were testing it with.

Once you have the launcher compiled for your cell phone, it will directly download start the browser for you:

PICTURE ONE

You can now browse through the different categories on the appstore:

PICTURE TWO

When you chose one, you get additional information about it:

PICTURE THREE

Download and run the app:

PICTURE FOUR

## For advance users and developers ##
### Developing software ###
To make your own applications you first need to visit MoSync's website at [www.mosync.com](http://www.mosync.com/) and download the software development kit (SDK). A complete tutorial is also found on the site.

### Submitting your software ###
At the moment applications can only be added by manually editing the SQL database. This can only be done by the people working on the project, since the project is this in a alpha state. In the future we might add something that will let user upload their applications by themselves.

### Setting up a server ###
Download the code for the Java server, and set up the PostgreSQL databse. Or make one of your own. It needs to be able to recivie XML request files, and fetch information from the server which then is sent back to the cell phone.