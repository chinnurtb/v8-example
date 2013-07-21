Why did I make this?
--------------------

Most articles regarding V8 that I found were for an older version that used now-deprecated functions and types, including [Google's Embedder's Guide](https://developers.google.com/v8/embed) (which, sorry Google, I didn't find very straightforward when I started using V8). This is just a small collection of the information I've gathered from the internet (every article I've read has the same thing based off of the original on [CodeProject](http://www.codeproject.com/Articles/29109/Using-V8-Google-s-Chrome-JavaScript-Virtual-Machin)) and the [v8-users Google group](https://groups.google.com/forum/#!forum/v8-users) that shows how to use the newer API.

How do I get V8?
----------------

No binaries are provided by Google, and as far as I know none are openly available on the internet. Just go ahead and follow the [download and build guide](https://developers.google.com/v8/build). It's quite painless, trust me.

Okay, now how do I use this example?
------------------------------------

Easy peasy! Take my hand, and I will guide you on your journey.

Files:
* **main.cpp** - Contains two functions: *ReadFile* and *main*. I'm sure you know what the latter is, and the former simply returns a V8 object representing the contents of a file. Don't know what a handle is? The [Embedder's Guide](https://developers.google.com/v8/embed#handles) does a pretty good job on that part.
* **console.hpp** + **console.cpp** - Contains an example of creating and binding a static object to some parent object (which is revealed to be the global object in **main.cpp**). In the *Test* method, I've also shown how to retrieve a C++ object embedded as a parameter in a function call.
* **point.hpp** + **point.cpp** - Contains an example of creating and binding an instance object to V8. The *Point* object contains two properties, *x* and *y*, along with one method, *print*, which I've set up to be a kind of two-birds-with-one-stone *toString()* method.

I've done a decent amount of commenting, so I'd like to think that once you take a look at the code and follow along (starting with **main.cpp**) you'll understand V8 fairly well. (At least as much as I do at the time of writing this.)
