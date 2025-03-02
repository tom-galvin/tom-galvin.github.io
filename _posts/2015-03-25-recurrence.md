---
layout: post
title: Recurrence Relations in F# and Haskell
date: 2015-03-25 19:43:31
summary: Building a generic solver for recurrence relations like the Fibonacci sequence.
categories: blog dev
---
The [/r/DailyProgrammer challenge last Monday](http://www.reddit.com/r/dailyprogrammer/comments/2z68di/) involved finding successive terms of a series, defined by a recurrence relation, given the first term of the series. The nice thing about writing these challenges is seeing the different types of solutions that people come up with. As it is a fairly simple challenge, most people opted to just repeatedly apply a function over and over to generate new terms of the series. Someone also created a [JIT compiler](http://www.reddit.com/r/programming/comments/2zlkor/) for the recurrence relation, which I really did not expect.

As I was aware that the second part of this challenge was going to be extending this problem to solve more complex recurrence relations, I created a [somewhat over-developed solution](https://gist.github.com/tom-galvin/796387d5acef8bf5394c) to solve both parts of the challenge at once. It's written in F#, a nice language that I've recently been playing with, that is quite accessible to me due to its basis on the .NET Framework. Having used C# before, the jump from one language to another wasn't so harsh.

When the time rolled around to submit the [second half of the challenge](http://www.reddit.com/r/dailyprogrammer/comments/2zna5q/), however, I was not on a Windows machine. F# (and Mono in general, as I have found) are a bit painful to work with if you're not on Windows. I had already essentially solved the challenge, so I didn't feel like starting from scratch; therefore I opted to do something I had been putting off for a while - to learn Haskell. It's a functional language similar to F# in style and syntax, and as learning a new language is a new year's resolution of mine, I decided to bite the bullet and re-write the solution in Haskell, learning the language as I go along.

The original F# solution used a `seq` to lazily generate the sequence as needed, using `Seq.unfold` to create a sequence with a state storing the known terms in the series. Haskell is a lazily-evaluated language, however, meaning the sequence can be represented as a list without causing an infinite recursion. To store the recurrence relation (aka *successor*) itself, I'm using a custom data type which stores a tree of operations to perform:

{% highlight haskell %}
data Successor = Literal Double
               | Previous Int
               | Binary (Double -> Double -> Double) Successor Successor
               | Unary (Double -> Double) Successor
{% endhighlight %}


As you can see, binary and unary arithmetic operations are supported, as well as literals. The `Previous` node type is for referring to a previous term in the series, such as `(Previous -1)` and `(Previous -2)` for the last two values in the Fibonacci sequence.

<div style="text-align: center" class="light-bg-image">
  <img alt="A diagram showing the (n-1)th and (n-2)th terms in the Fibonacci sequence." src="{{ site.base_url }}/images/recurrence/sln1.png" /><br/>
  <span class="post-meta small">From this, you can see that the Fibonacci recurrence relation is <strong>dependent</strong> on the (-1)th and (-2)th term, relative to the current term.</span>
</div>

Hence, the `Successor` representing the Fibonacci sequence would be something like this:

{% highlight haskell %}
fibSuccessor = Binary (+) (Previous -1) (Previous -2)
{% endhighlight %}

My solution traverses the successor tree to find the list of terms that the defined term is dependent on (`[-1, -2]` in this case), by looking at the `Previous` nodes. Then, by taking this list, you can step along the *unknown* terms in the series, find out whether both dependent terms *are* known, and then calculate those terms and add them to the known terms in the series. By doing this iteratively, you can start from a small number of known terms in the series (such as `[0, 1]` in the Fibonacci sequence) and build up from there.

<div style="text-align: center" class="light-bg-image">
  <img alt="An animation showing the successive deduction of terms in the Fibonacci sequence." src="{{ site.base_url }}/images/recurrence/sln2.gif" /><br/>
  <span class="post-meta small">This might seem overkill for something such as the Fibonacci sequence, but this process supports the calculation of much more complex series, such as those with missing terms in the middle.</span>
</div>

Implementing the solution in Haskell wasn't too bad, even having never touched it before. The Hackage documentation is very comprehensive, and most map/reduce functions are the same across all languages, so it wasn't hard to get something up and running quickly. The ability to [search by type signature](https://www.haskell.org/hoogle/) was also useful.

## haskell

It helped me greatly that F# and Haskell are both somewhat similar. Despite both being from different families of languages (F# having descended from ML), I solved the challenge almost identically in both. F# does have a more imperative touch to it, however - the `|>` (forward arrow) operator is well used by F# code - for example, the visual flow of data generally goes from left to right (or from top to bottom, if split over multiple lines), like this:

{% highlight fsharp %}
let someValue = originalData
             |> List.ofArray
             |> List.map exp
             |> List.distinct
             |> List.fold (+) 0
{% endhighlight %}

In Haskell, however, the flow of data is reversed. Composition is mainly done with the `$` operator (equivalent to `<|` in F#), like this:

{% highlight haskell %}
let someValue = foldl (+) 0
              $ nub
              $ map exp
              $ originalData
{% endhighlight %}
<div style="text-align: center">
  <span class="post-meta small">Alternatively, Haskell allows the composition of functions with the <code>.</code> operator, which has the same functionality as the ring operator in mathematics, such as g&#x2218;f.</span>
</div>

Both examples represent chained function application, and out of the two languages, Haskell's preferred representation is the closest to what is actually happening:

{% highlight haskell %}
let someValue = foldl (+) 0 (nub (map exp (originalData)))
{% endhighlight %}

In this way, I suppose F#'s `|>` operator reverses the application of functions by putting the argument first, even through this is what makes more intuitive sense (especially coming from an imperative language, where operations are specified sequentially). Either way, if you're coming from F# to Haskell and you want to make it seem that *little* bit more comfortable, you can always re-define the `|>` operator and use it as you normally would.

{% highlight haskell %}
let a |> b = b a
{% endhighlight %}
<div style="text-align: center">
  <span class="post-meta small">Not that I would recommend you do this. It's not exactly idiomatic Haskell, and it doesn't take long to get used to reversing the order of functions.</span>
</div>

If you want to see my solution to the challenge, there's the [Haskell version](https://gist.github.com/tom-galvin/d58bfeef18855ef11d4b) and the [F# version](https://gist.github.com/tom-galvin/796387d5acef8bf5394c) - the only difference being that the F# solution doesn't accept the RPN input for Part 2 of the challenge. The use of `++` in `getSeries` is a little bit nasty, but I only found out that it runs in *O(n)* time after writing the solution.
