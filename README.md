WEASEL defeats bazel

> To this dreadful monster the effluvium of the weasel is fatal, a thing that has been tried with success, for kings have often desired to see its body when killed; so true is it that it has pleased Nature that there should be nothing without its antidote. The animal is thrown into the hole of the basilisk, which is easily known from the soil around it being infected. The weasel destroys the basilisk by its odour, but dies itself in this struggle of nature against its own self.


After spending too much time trying to build tensorflow both with -O2 and -g here is what we do:
Create a small tool that mimics the compiler in a way similar to ccache and _edit compilation options on the fly_.

One way to use ccache is to make /usr/lib/ccache/ to show-up before compilers. This dir holds links named 'gcc', 'g++' etc. pointing to the ccache binary. Once ccache is called it looks for compilation products in the cache and serves them or falls back to calling the actual compiler. Weasel-b should be used in the same way, only it will call ccache after it's done editing arguments. You have to compile wasel and create a directory with links pointing to it

A small bonus is that it is also going to produce compile\_commands.json to be used with YouCompleteMe after small post processing (surround with [ and ], add base directory to files that aren't absolute)


