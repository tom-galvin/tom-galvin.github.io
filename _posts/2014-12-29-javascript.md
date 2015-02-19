---
layout: post
title: "JavaScript: What it is, shouldn't be, and could have been"
date: 2014-12-29 16:26:06
summary: "With JavaScript turning into the new Ruby as Ruby turns into the new Python I thought I'd give my piece as the Ghost of JavaScript Past, Present and Future."
categories: blog dev
---
The Web has seen a peculiar inversion over the past few years. JavaScript started out purely as a client-side layer over the HTML page; something that web developers added to statically served sites to make them seem a bit less flat - that is, when they weren't using the `<marquee>` and `<blink>` tags in a convoluted honeycomb of `<frameset>`s. This is the same time when a lot of sites were written as huge monolithic slabs of ASP code, meaning the front-end developer and back-end developer was often the same person.

<div style="text-align: center">
  <img alt="ASP... kill it with fire!" src="{{ site.baseurl }}/images/asp.png"/><br/>
  <span class="post-meta small">An ASP (Active Server Pages) server error, ubiquitous for causing software developers hours of pain.</span>
</div>

This is also the same time when people weren't ashamed to have their entire website consist of a Shockwave Flash object, Java applet or (ack) an embedded ActiveX control. These were certainly not *good* times - the situation has improved significantly since those days, don't get me wrong. But for it's time and it's purpose, which was to accompany Java as a less enterprise-y language for the so-called "scripters"[^1], JavaScript did its job.

Recently, however, the relative attention that JavaScript and HTML receive has switched. The Web isn't seen as *HTML (with JavaScript)* anymore, it is *JavaScript (via HTML)*. The majority of public-facing pages use jQuery (or other similar libraries) for interaction, with HTML and CSS often acting as a thin layer over a huge JavaScript backbone. Entire websites written in JavaScript now not only exist but are commonplace with frameworks like [ember](http://emberjs.com/) and [angular](https://angularjs.org/). JavaScript has also leaked out of the browser, resulting in projects such as [Node.js](https://www.nodejs.org/) with which JavaScript is ran server-side. This allows entire stack-wide frameworks such as [meteor](https://www.meteor.com/) to exist.

I will accept that using the same language on both the client and the server can be good for a lot of reasons, but at this stage, it seems like developers are shoe-horning it into every possible application that it will work in. In general, this isn't necessarily a bad thing; both Java and Python have received similar treatment at some point. However, as a language initially designed to be Netscape's analogue to Visual Basic[^1], it certainly wasn't designed for these targets.

## what it is

JavaScript is a multi-paradigm language that has drawn features from several different languages. The syntax is distinctly C-like, what with the C-style 3 part `for` loop declaration and curly-brace block delimiters. It borrows inline regular expressions from Perl (which also influenced Ruby), allowing code such as `/([-A-Za-z0-9_]+?):(?:\w*(-?[0-9]+))*/` to denote a PCRE literal. JavaScript also notably has first-class functions, allowing lisp-like form of functional programming to be done. More importantly, though, JavaScript has a somewhat esoteric type system based on [prototyping](http://en.wikipedia.org/wiki/Prototype-based_programming), which does away with a class system, instead cloning existing 'prototype' objects. This allows several paradigms of object-oriented programming to co-exist, including duck-typing, mixins and bog-standard inheritance - none of which look too pretty in JavaScript. The language's roots as the manipulator of the DOM necessitate its role as an event-driven language, too, something which works well with the functional aspect of the language.

This means JavaScript works quite well for a lot of different things: it can be used imperatively to make small tweaks to web pages in the browser, it can be used as an OO language to manipulate data, and now with the advent of WebGL it can be used for accelerated 3D graphics and physics simulation in the browser with libraries such as [three.js](http://threejs.org/) and [physi.js](https://github.com/chandlerprall/Physijs), which is particularly cool (and works surprisingly well). The expressive syntax of jQuery often borders on being declarative. Somewhat ironically, I think OOP is one of JavaScript's weak points - the syntax for creating something reminiscent of an object class isn't very pretty and varies somewhat from developer to developer:

{% highlight js %}
function Thingy(myName) {
  this.myName = myName;
  this.stuff = [];
}

Thingy.prototype = {
  whatsit: function(val) {
    console.log(this.myName);
    this.stuff.push(val);
  }
};

var v = new Thingy("Stan");
v.whatsit(123);
{% endhighlight %}

ECMAScript 6 brings some nice gems, though. One that I'm a big fan of is C#-esque lambda expressions with fat-arrow notation:

{% highlight js %}
var square = x => x * x;
{% endhighlight %}

It also brings more familiar class syntax, using the `class` keyword and supporting Java-like `super` base constructor calls. It even brings Rust-like pattern matching for `var`/`let` statements, which is particularly nice. Finally it brings lazy iteration to `for` loops, ringing of the .NET framework's `IEnumerable`. This has singificantly improved the language itself, making it more familiar to developers of other languages. Waiting for browsers to implement ES6 will be another matter; I currently use Firefox, which does support the new syntax, but I know many browsers don't at the time of writing. Nevertheless, this is only one half of the story.

## what it shouldn't be

Despite being usable for a lot of things, JavaScript is definitely not perfect. It has an unnaturally large number of quirks and oddities that can make it seem downright hostile to a developer attempting to learn JavaScript as a first language. The equality operator has been unusable for anything for a long time. `[[31]] == "31"` and `null == undefined`, due to the strange implicit type conversion rules applied by the `==` operator; the `!=` operator behaves similarly. To get around this, instead of fixing what can only be described as broken behaviour, the `===` and `!==` operators were introduced. However, if a script relies on such broken obtuse behaviour then (in my opinion, at least) breaking it should not be a concern. This sort of backward-compatible fix rings of `mysql_real_escape_string` in PHP[^2]. However, this doesn't fix the rest of the operators; `[4]` divided by an empty string is still infinity, and `'3'` is greater than `/6/`.

Any sensible language would raise some form of error with these expressions; dynamic typing isn't a bad thing, but implicit type coercion certainly is. You can use helpful tools like [JSLint](http://www.jslint.com/) to capture these nasties before they end up in production code (I've put a `==` in place of `===` too many times to be comfortable) but these tools are signals of a larger problem with the language, rather than a permanent solution. This behaviour is totally unpredictable; the `+` operator isn't even commutative in this situation, which is very unintuitive:

{% highlight js %}
> [] + {}
[object Object]

> {} + []
0
{% endhighlight %}

Again, this shouldn't even work at all, but at a *bare minimum* these two expressions should be equal. A language with such arbitrarily-defined core behaviour really shouldn't have gotten as far as it has done. Ideally, once people realised that JavaScript was going to be much more than an interactivity tool, it should have been replaced or superseded by something more concrete and suited for larger-scale development, such as [Dart](https://www.dartlang.org/) or [CoffeeScript](https://www.dartlang.org/). To me, hearing that Gmail is primarily written in JavaScript is like hearing Apache is mostly written in shell script (which it isn't, thankfully) - sure, it might work, but it's like ramming a circle in a square hole. At this point now, though, JavaScript has such a large and well-rooted ecosystem surrounding it that it's not really worth making the switch. People have gotten used to the weirdness of the language, and worryingly even embraced it.

I think one of the things that doesn't help is that a highly dynamic language like JavaScript uses syntax so close to languages like C and Java, which both feature admittedly verbose syntax but highly predictable behaviour. Developers like it when they can look at a piece of code and predict accurately what it's doing to do, rather than have to look up two different sets of documentation and hunt around on StackOverflow. Developers don't want to work around the weirdness of a language - that was, after all, the initial point of using languages at all: to abstract away the intricacies of the underlying components into something consistent and predictable on every platform. Excessive boilerplate code is a sign of an unsuitable language, and I believe at this stage having to use something like jQuery can be described as boilerplate. This part certainly isn't directly a fault of the language itself, because it's a relatively robust scripting language when you look past the flaky syntax. The main issue is with the highly variable implementation of it, and its overuse since people got swept up in the HTML5 hype train.

## what it could have been

Hindsight is 20/20, especially in the world of development. On such a variable platform like the web, where content from this morning and from 12 years ago can co-exist, this phrase is especially accurate. The ecosystem and community surrounding JavaScript is certainly one of a kind, and it's turned something lumpy and weird into something usable and beautiful. At its conception, JavaScript was ideal, as there really was no other imaginable alternative. Brendan Eich couldn't have known that, 10 years down the line, entire software stacks would be written in the little scripting language - in the same way that the creators of PHP couldn't have known that their basic webpage preprocessor was going to be the target platform of a gargantuan site like Facebook.

These languages have gained their negative connotations in the eyes of developers, principally because of what developers have tried to make them become. I'm sure if AppleScript was chosen as the successor to JavaScript, it too would be reviled as a language of the Web, even though it's a perfectly good UI automation tool.

If we could all collectively travel back in time 10 years, to give our past selves some advice, then the advice would probably be to leave JavaScript where it is, and to develop another language with the flexibility of JavaScript, the consistency of Java, and works predictably and consistently on every platform. It needs to work well as both a compiled (for the server side) and an interpreted (for the client side) language, and libraries like jQuery (or an adaptation to suit the strong points of the new language) should be part of the standard library.

This is not an easy task to undertake - I hesitate to say that no language that currently exists can fill this role. Dart's a nice language, but perhaps not ideal for large whole-stack frameworks[^3]. Rust is extensible and predictable, but is a systems language. I'd like to say Ruby is a suitable candidate but the language would have to be tweaked somewhat to play nicely with compilation. CoffeeScript has nice expressive syntax, support for existing JavaScript libraries, and can compile directly to JavaScript, and ECMAScript does turn the language into something that is nice, workable and expressive.

However, *JavaScript two point oh* is not what we need. It would be difficult to get everyone to sit down and go to the drawing board on this one, but I think it's becoming increasingly necessary as JavaScript becomes increasingly cumbersome in order to keep up with the demands the world puts on it.

[^1]: [http://brendaneich.com/2008/04/popularity/](http://www.computerworlduk.com/blogs/open-enterprise/mozillas-brendan-eich-on-javascript--and-microsoft-buying-netscape--3569135/)  
[^2]: PHP has since introduced PDO for database interaction, which is actually one of the nicer improvements of PHP - certainly better than manually interpolating variables into query strings. Bobby Tables, anyone?  
[^3]: Dart and Rust are two of the languages on my list of cool things to try out some day. They sound great, but they'll need some time set aside in order to get to grips with.
