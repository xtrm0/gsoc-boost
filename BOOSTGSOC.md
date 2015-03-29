Boost Google Summer of Code 2015 Application
=======================================================
+5.Enhanced vector and deque containers proposal


Personal Details
----------------

  - **Name:** Afonso Tinoco
  - **University:** Instituto Superior Técnico - IST (Portugal)
  - **Major:** Master in Aerospace Engineering (alongside with a Master in Eletrotecnical and Computers Engineering)
  - **Email:** afonso.tfaria21+boost@gmail.com
  - **Homepage:** github.com/xtrm0 (I have no projects in here that you should look at. None of them is in c++ and none of hem reflects my programming habits)
  - **Availability:** I'd like to spend 30 hours/week on GSoC until the end of July, 40 hours after then.
      I want to start as soon as possible. My availability will be lower on July due to college exames, but after such
      period i'll have an infinite ammount of time and energy to dedicate to boost.




Background Information
----------------------

_Please summarize your educational background (degrees earned, courses taken, etc.)._

I'm on the 2nd semester of the 1st year of my major+master in aerospace engineering. During this semester, I've also started to take courses in a second major+master
in Eletrotecnical and Computer Engineering, because I like computers and the challenge of taking two majors at the same tame amazes me.


_Please summarize your programming background (OSS projects, internships, jobs, etc.)._

I've been programming since I was 13 or so. I started to learn C and quickly moved to C++. From my 9th grade to my 12th grade
I participated at IOI, due to which, regardless of my results of which you don't care, I developed a strong knowledge of C++.
During the last few years I've developed small useless projects, some of which you can find on my github page (even though those are really poor).
Currently I'm working on two diferent project:
+ As a server side developer for our startup uniwee
+ As a web developer for JUNITEC (Junior Enterprise of IST)


_Please tell us a little about your programming interests._

I'm mostly interested in the field of algorithms and optimization. It's an area that has always fascinated me
I've never built a library in C++ but this seems an interesting enough project for me to start.


_Please tell us why you are interested in contributing to the Boost C++ Libraries._

I'd love to contribute to the Boost project for two main reasons:
+ I believe in Boost mission. I believe having full range ready to use libraries is an important part of any project, that not only reduces development time, but also greatly reduces the prone to mistake.
+ I've never participated in any big open-source project and I find boost a good place to start, not only for the great community, but also for the big ammount of feedback the code would get.


_What is your interest in the project you are proposing?_

First of all, it would be a great accomplishment for me to develop such a basic and broadly used part of the Boost libraries as the vector is.
Second, developing a small improvement on STL containers means they might get implemented into STL, and that would be awesome.
At last, the challenge of developing such containers as good as possible is one I'd like to face and beat.


_Have you done any previous work in this area before or on similar projects?_

I'v never participated in any opensource project nor developed any library with rigor, but there's a first time for everything!


_What are your plans beyond this Summer of Code time frame for your proposed work?._

I'd love to hear about the community feedback on the project and submit some patches on it. Also if it's ok, I'd love to be the mantainter of the (de)vector project, or in case the comunity is feeling realy kind of both the (de)vector and deque.


_Please rate, from 0 to 5 (0 being no experience, 5 being expert), your knowledge of the following languages, technologies, or tools:_

The following are rated as a skills of a student:

  - **C++ 98/03**: 4.3, I'm mostly familiar with this standard, there isn't much I don't know how to do/how it works.
  - **C++ 11/14:** 3.8, I understand most of the new standard, but mostly I assume everything works as it did in 03, due to not having read enough reference yet.
  - **C++ Standard Library:** 4.5,  
  - **Boost C++ Libraries:** 2, I worked only with the following libraries:
      Algorithm, Regex, Filesystem, Test
      The others I have little or no experience with. I'm also only very well familiarized with Regex and Test.
  - **Git:** 3.7, I use it almost everyday and am familiar with the most important commands, however noone can master git


_What software development environments are you most familiar with (Visual Studio, Eclipse, KDevelop, etc.)?_

[On Linux: (I use mostly fedora 21)]
+Editors: Emacs and eclipse CDT or atom
+Compilers: gcc and clang
+Debugers: gdb is my main option, but I have some small experience with lldb
+Memory testing: valgrind

[On Windows: 8]
+I prefer using visual studio 2013

_What software documentation tool are you most familiar with (Doxygen, DocBook, Quickbook, etc.)?_

I'm only familiar with Doxygen and have never used any of the later, yet I'm able to do so if thats what the comunity wants.


Project Proposal
----------------
> For certain applications the standard containers std::vector and std::deque are not too easy to work 
> or may induce unnecessary overhead. For example, std::vector lacks an O(1) time push_front 
> and std::deque allows you no way of controlling the size of the underlying segments. 
> This limits their usability in certain contexts, especially if you want to have optimal performance. 

I propose to write an enhaced version of `std::vector` and `std::queue` in C++11.

In case of `vector`, I propose to write a version with O(1) push_front, pop_front().
To do so I rigth have two options that I'd like to discuss with the mentor//with the comunity:
1) Keep the data in the middle of the allocated memory, allowing for O(1) insertion and retrival in exchange for a bigger
insertion/removal average constant and memory footprint, when compared to the std::vector.
1.1) Allow the user to control how the memory gets allocated in push_back//front, when a resize happens, leavin up to him to tweak the constants.
(But the default behavior would be too keep data on the center of the allocated memory)
2) Use a circular queue, allowing to keep perfomance and memory constants as good as std::vector, while loosing the contiguos data property.

In case of `deque `, I'd also like to discuss this with the mentor, as we have several things we can implement:
1) Allow the user to specify the block size at the queue creation or with an O(n) operation change_block_size().
2) Allow min(n/m, m), random insertion, by using a circular queue.
3) Allow the user to specify the size of any block allocated, losing the O(1) insertion to have an O(log n) insertion, in exchange for a better memory footprint.


Schedule
--------------------------------

I propose the following time ratios:

 - **1/8** Discussing implementations for vector
 - **1/4** implementing vector
 - **1/4** Discussing implementations for queue
 - **1/4** implementing deque
 - **1/8** writing documentation
 
 
 I propose to have completed the following at the respective dates:

 - **1  June**: Decide on the vector implementation
 - **8  June**: Implement Vector
 - **15  June**: Test vector. Correct bugs.
 - **22 June**: (I can't work this week here due to exams)
 - **6  July**: Create some basic deque implementations
 - **13 July**: Analyze the implementations and decide with the mentor//with the community
 - **20 July**: Implement the final version deque
 - **27 July**: Test deque. Correct bugs
 - **3  August**: Create initial documentation
 - **10 August**: Documentation should be finished by this date.
   Implement Community suggestions
 - **17 August**: Implement Community suggestions


Programming Competency
----------------------
 
I have just uploaded my programming competency test to github,
allong with an initial implementation of the (de)vector.
The competency test is on the root folder and the devector initial implementation is on the devector folder of: https://github.com/xtrm0/gsoc-boost

[github]: https://github.com/xtrm0
[comptency test]: https://github.com/xtrm0/gsoc-boost

[note]: this application template is based on another I found on the boosts mailing list (even tough I can't remember which on it was anymore)
