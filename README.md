Never having being a professional coder nor having written code for years, I was reminded how hard it can be to start a C++ project when I started again recently. While I have grand ambitions, my experience slogging though a maze of document with many dead ends, made me decide to create and persist this 'starter project'. There are many of these around on GitHub but I soon realised that the fast moving world of standards, libraries and community projects, means there are often just better ways available to someone starting fresh. No doubt this will also be the case for you but the time you read this. Be that as it may, I found the ability to quickly clone a starter template and see what happened, greatly enhanced my ability to make some progress. I hope this may help you in the same way but please 
note - I'm really not that good at this so don't be overly hasty to adopt my suggestions!

Aim: I wanted to create a C++ library with a test harness, a executable front end and a python module. I wanted to create this to be compiled across platforms because I have a hunch that I really want the end product deployed in docker (although there is nothing here about docker - that may come later). I wanted to start fresh so that I could explore all the fantastic new stuff in C++ as a result of all the new standards. To that, here are some of the decisions I made
- I used Visual Studio Code (1.46.0) because I wanted to interact with the project in Windows and Linux (with the aim of ensuring that a move to docker may be easier if I was not doing platform specific stuff)
- The following extensions for VSCode
    - The ms-svcode.cpptools extension (https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
    - CMake Tools (https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
    - CMake twxs (https://marketplace.visualstudio.com/items?itemName=twxs.cmake) - for cmake sintax highlighting

Package Management: vcpkg

Testing





In case you are really, really bored!
A few years ago I wrote some code to 'structure derivative transactions' using excel as the front end. I was inspired by Quantlib.org but wanted to use the exercise to force myself to put in some time and effort into C++. I also wanted something less 'quanty' (read simpler) because had hoped to deploy my work for a foar less technical user base. A user base that understood their specific market well and 'knew' there was only one way to price those derivatives and just wanted 'that stuff' to be hidden from them. My main aim was to build a Monte Carlo Engine for derivative structures they composed, or added to, in order to calculate Risk and Finance measures that needed Full Monte Carlo (PFE, xVA, Basel Regulatory Capital etc).

I really struggled but managed to cobble something together. Even though I tried to build the code properly, there was just too much that I had to learn so, while it worked, it was a bit of a Frankenstein, parts borrowed from QuantLib, parts taken from Steve Dalton's book Excel Add-in Development in C/C++. While I was really happy the project managed to achieve it's objectives, it never really gained much traction - even a light structuring library gets quite messy and asking traders to choose between risk-neutral and real-world evolution of stochastic variables made the spreadsheets too difficult to use. It still required an expert audience. 

I have not written any code for a long time now, being involved in 'management' as a day job (try to avoid this if you can). Anyway, I wanted to try something similar again. This time though I am not going to worry about excel. This time I want to get my code deployed and working in the cloud via APIs (which I could call asynchronously from excel if I really need to). 

Again, most of this is new and foreign to me but the best way to learn is to try. I have been amazed how hard it was to start however so 

