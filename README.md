
# What is this?
The start of a Derivative Monte Carlo engine. I wanted to pick up some C++ and felt I had to justify the use of a complex environnement with something that performed a lot of calculations.

I have [starter project](https://github.com/sjondavey/cmake-starter) to test out the build environnement and tools. It was hard to get to the point where I could write code. In the end, I had to make compromises and leave things before I really understood what was happening. Hopefully it's still relatively easy to follow.

## Use
The project builds an equivalent of 'montecarlo.cp37-win_amd64.pyd' in Windows under the build directory. If you launch a Python from the command line in this directory they the tools is accessed as
```python
import montecarlo as mc
help(mc.call_value)
mc.call_value(100,110,0.2,0.98)
help(mc.Black76Call)
call = mc.Black76Call(100,110,0.2,0.98)
call.delta()
```




## In case you are really, really bored!
A few years ago I wrote some code to 'structure derivative transactions' using excel as the front end. I was inspired by Quantlib.org but wanted to use the exercise to force myself to put in some time and effort into C++. I also wanted something less 'quanty' (read simpler) because had hoped to deploy my work for a less technical user base. A user base that understood their specific market well and 'knew' there was only one way to price those derivatives and just wanted 'that stuff' to be hidden from them. My main aim was to build a Monte Carlo Engine for derivative structures they composed, or added to, in order to calculate Risk and Finance measures that needed Full Monte Carlo (PFE, xVA, Basel Regulatory Capital etc).

I really struggled but managed to cobble something together. Even though I tried to build the code properly, there was just too much that I had to learn so, while it worked, it was a bit of a Frankenstein, parts borrowed from QuantLib, parts taken from Steve Dalton's book Excel Add-in Development in C/C++. While I was really happy the project managed to achieve it's objectives, it never really gained much traction - even a light structuring library gets quite messy and asking traders to choose between risk-neutral and real-world evolution of stochastic variables made the spreadsheets too difficult to use. It still required an expert audience. 

I have not written any code for a long time now, being involved in 'management' as a day job (try to avoid this if you can). Anyway, I wanted to try something similar again. This time though I am not going to worry about excel. This time I want to get my code deployed and working in the cloud via APIs (which I could call asynchronously from excel if I really need to). 

Again, most of this is new and foreign to me but the best way to learn is to try. I have been amazed how hard it was to start however so 

