---
layout: post
title: "On Boolean Algebra and Type Theory"
date: 2014-12-27 20:30:15
summary: "An interesting parallel between boolean algebra, type theory, and indeed almost anything with a + and × operator."
categories: blog cs
---
In an attempt to better understand and use functional programming languages like Haskell, I've been delving deeper into the Computer Science theory behind it all. This typically involves staring intently at Wikipedia pages on the topics rather than receiving any form of formal education on them, but that's generally enough to glean some worthwhile information.

Boolean algebra is a mathematical model for binary logic, using only the values `True` and `False` (or one and zero) for variables. To represent logical *or*, the addition symbol can be used, and likewise the multiplication symbol for *and*<sup>[1]</sup>. The choice of these symbols becomes immediately evident when you use one and zero; the multiplication table corresponds directly to the *and* truth table. Zero multiplied by anything is always zero, meaning the value of **A**×**B** can only be non-zero when **A** and **B** are non-zero. Similarly for addition, for **A**+**B** to be non-zero, either **A** or **B** must be non-zero. Of course, one plus one is two, but two doesn't exist in the mind of George Boole, so the result is limited to the values {0, 1}.

Type theory, like Boolean algebra, describes a real-world situation in a mathematical way. It can be used to describe the type systems in many languages in a more constructive manner; for example, the ubiquitous tuple data type can be understood to be the product of its constituent types; a tuple of two integers can be described with the type `Int×Int`. In my mind, the parallel appears when you read this like Boolean algebra: a tuple of an `Int` with an `Int` is the same as `Int` and `Int`. In my mind, this helps to further the distinction between a tuple and a list or array: the two types are inseparably joined together, like the immutable tuple type.

The tagged union is perhaps the unsung hero of functional data types. It is one of data structures in general; describing something as being either one type or another is a fairly principal idea in most programming languages. A prime example of a tagged union is the `'t option` type in F♯, where something can be either `Some(...)` or `None` - equivalently, the `Maybe a` in Haskell is either `Nothing` or `Just a`. Tagged unions are also used in a round-about way to describe the class system in OOP languages. Tagged unions are doable in languages as simple as C:

{% highlight c %}
struct tagged_union {
    enum {
        IS_A_FLOAT,
        IS_AN_INT
    } type;
    union {
        float f;
        int i;
    } data;
};
{% endhighlight %}

Tagged unions can also be represented in type theory, using the `+` operator (you can probably see where this is going now). A type which can be either `Int` or `Float` can be written as `Int+Float`. Reading this like a boolean algebra expression suggests the exact same thing: `Int+Float` is `Int` or `Float`, which is exactly what a tagged union (or a Rust-style `enum`) represents. This way of thinking really helped me to understand what was going on inside the more algebraic type systems featured by the likes of Haskell and OCaml (and by extension F#), and hence I feel that getting some form of grounding in the underlying theory behind types and other things like categories is a helpful (and often necessary) exercise in learning what's really going on in a functional language, which is after all an attempt to model a computer program using maths.

Of course, it gets a little weird once you introduce [quotient types](//en.wikipedia.org/wiki/Quotient_type) - it's that point when weird words like "setoid" and "surjective partitions" start flying around when I close the tab and start browsing Reddit again.

<sup>[1]</sup>: Some prefer to use the notation from formal logic for Boolean algebra, using `∧` and `∨` in place of `×` and `+`.
