---
layout: post
title: "2015: Targets and Resolutions"
date: 2015-01-02 13:50:32
summary: "I present some targets for the new year: some new, and some long overdue."
categories: blog gen
---
I've been putting a few things off recently so I can make them resolutions for the new year. Some are new targets I've set myself, and some are things I should've done a long time ago.

## rust

I've been working on a programming language recently which I mentioned in [my parsing post]({% post_url 2014-12-25-parsing %}) a week ago - the compiler is written in C. C is undoubtably a brilliantly useful language: it's available on essentially every platform to some extent, it's predictable[^1], stable and simple, which are 4 good traits. However, it certainly isn't ideal. One bad thing about C is that things generally take a long time to write in it. I realised after writing the parser that at least 70% of the time I had spent was just writing boilerplate code, such as memory management and cookie-cutter RAII functions. While C is useful to know for a variety of reasons, I feel that using C for everything is a bad habit to slip into; it has its place, which generally isn't for medium-scale hobby projects. There are a few alternatives:

* Scripting languages let you develop the project relatively quickly, but they are perhaps not too suitable for projects such as parsers, although I am still seriously considering it.

* C++ would be somewhat better than C, but I'm not too well versed in it - especially with regard to the different pointer types in C++11/C++14 and the template system. I feel that writing good modern C++ involves using awkward clunky syntax, and having to work *around* the language just to use it effectively is a bad thing.

* Java is a solid choice but the warts of Java come out to play with larger projects, such as the underpowered type-erasure generics and the patchy standard libraries (it seems that I have to use the Apache Commons library far too often), which I've stubbed my toe on too many times to feel happy working with Java.

* C# would be my go-to choice if not for the fact that I'm currently not on Windows and the .NET framework is currently too closely tied to Windows to feel comfortable using Mono (although this [shows signs of changing soon](http://blogs.msdn.com/b/dotnet/archive/2014/11/12/net-core-is-open-source.aspx)).

* I don't know enough about Haskell (or FP in general) to start a project in it, as this will inevitably lead to me making bad design choices.

* Google's Go language feels artificially limited and too simple; the purposeful exclusion of generics is a large red flag for me, as it seems that this choice encourages code repetition. I understand why it was done; my main problem with it is the lack of a solid replacement, and the workaround is to use reflection which defeats the purpose of omitting generics from the language in the first place. It looks like a nice language to learn but I won't prioritise doing so.

I also feel that it's important to keep up with modern technologies and projects. For this reason, I resolve to learn Rust at some point this year, at least to the point of competence on medium-scale projects. This won't be a quick thing to do, but it will certainly be a useful skill at some point. It's a low-level systems language by Mozilla that also has expressive syntax and has some FP-esque features, especially in the type system (which differs from conventional OOP slightly, but not too much to feel alien). It's designed to be a modern replacement for C++ which shaves off some of the gotchas of old languages. It's also built from the start to have an ecosystem (one of the reasons I like C#), such as the inclusion of a package manager (Cargo) from the start. Currently it's at a pre-release stage, meaning it won't be bogged down with preservation of backward compatibility, but also mature enough to remain relatively consistent. Lastly it uses scope ownership for memory management and RAII for resource management. This strikes a nice balance between full on garbage collection and C-style manual management, while also avoiding the mistake that modern C++ is now having to rectify.

## web frameworks and architecture

I'll inevitably end up using one of these at some point, so I might as well get used to it. I have already used ASP.NET MVC before (to an extent) so unlike learning Rust I have a bit of a head-start. I have also played around with Sinatra a little bit, but not enough to be well-acquainted with it. Of course it wouldn't be too much use learning just one such framework, so I also intend to learn the underlying principles behind them.

One example is the differences between the various paradigms of web framework and the subtleties of each one. I know what the likes of MVC, MVP and MVVM *are* but not necessarily the specific situations where each one would be used, and the benefits and drawbacks of each one. The more advanced concepts of routing and web design patterns are also something I'm interested in getting to grips with.

Lastly, knowing the basics of server architecture in general will benefit my understanding of the previous two. This includes security and the concepts of HTTPS, load balancing and database architecture. This sounds a tad gruelling, but I think that it's worth learning these things now rather than 10 years down the line.

## portfolio

I have a habit of starting a project on GitHub, growing bored of it (or hitting a wall) and then leaving it, the reasons for which I touched on in the first section. Having some evidence of prior work would be beneficial and platforms such as GitHub and Bitbucket are ideal for this. I have made some contributions to open-source projects, but not nearly as many as I'd like to have done at this stage, so being more proactive in this regard is something else I resolve to do in 2015: to start something, and to conclude it some way or another.

## cubing

One of my hobbies is [speedsolving](http://en.wikipedia.org/wiki/Speedcubing) which I've been doing for about a year now. I'm Sub-25 on the 3x3 and I average about 90 seconds on the 4x4 (I'm not too interested in speedsolving anything larger as the puzzles tend to be less structurally stable and are prone to flying apart), and I also sometimes try speedsolving the 2x2, but my method isn't too efficient there.

<div style="text-align: center">
  <img alt="An image of a 6-by-6 cube puzzle that has broken quite dramatically." src="{{ site.base_url }}/images/cube.jpg" /><br/>
  <span class="post-meta small">The reason why I stopped bothering to speedsolve larger cubes.</span>
</div>

Hopefully I can learn a subset of full OLL for the 3x3, get better at Yau on the 4x4, and learn one of the dedicated 2x2 methods to be a bit faster. Currently I just use standard CFOP for the 2x2 which works but is certainly not fast. Something like Ortega or Guimond would be relatively easy to learn and also bring my times down considerably, so my final resolution is to learn a 2x2 method, improve my 4x4 time and get to Sub-20 on the 3x3.

### finally...

Of course, these aren't my only resolutions, but the rest of them are probably of little interest for this type of blog! Have a good year.

[^1]: Unless you introduce undefined behaviour, in which case the language becomes anything *but* predictable.
