I wanted to experiment with packaging stuff into .exe's and some CLI related code and this is what happened. Git Bash, but with cats. Feel free to add whatever you want to it.

![Screenshot of Catbash](funbash.png)

Update 11/12/25:
Broke my big monolothic code structure into a bunch of more organized files. From now on I'll try and write down every time I try to use a command or something and it doesn't exist, and I'll add it every month or so.

Update 11/11/25: 
There was a llama.cpp flag the whole time. Added and quantized gemma is now working. Additional threads were not necessary.

Update 11/10/25:
I decided to try and add a small LLM to catbash so that you can ask it basic coding questions and command help as you work if you forget something. Since the base I created works pretty well, I imagined it would be pretty easy. It was in fact not easy. I first tested out stuff with a quantized version of Microsoft's Phi 2, but it hallucinated no matter how much "prompt engineering" I did and was not very helpful. Moving over to a quantized Gemma model from around a year ago has given me much better results. The only problem is, regardless of what flags I use, the model will get stuck in an interactive mode where everything you say to it, including commands, is just considered an LLM prompt. As far as I can tell, my use case and the constraints of running an LLM in this manner makes this stuff annoying to deal with and common. I'm guessing I'll have to run it on its own process and then kill it once it's done dealing with the prompt, so I will study how to do that tomorrow. 

TLDR: Tested models, old ones aren't good (as expected). LLM's get stuck in interactive mode (considers all commands prompts instead of command-ing) and no way to close out (ctrl-c kills the terminal along with the running LLM). Solution: dedicated process for the LLM, and study how to implement.
