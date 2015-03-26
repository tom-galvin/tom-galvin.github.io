---
layout: post
title: Lessons learned from a successful project
date: 2015-02-19 22:13:36
summary: Some morsels of wisdom picked up about using WinForms and GDI+ in my A-level Computing coursework.
categories: blog dev
---
I'll start by admitting that my started-to-completed ratio of projects is shocking: I have many half-baked ideas in several different languages and frameworks cluttering my hard-drive. A lot of these are due to time constraints, getting bored of the idea, or simply having the project run away from me - realising soon after starting that it's going to take a lot more effort to finish this than I had hoped.

I think the most important thing that you need in order to successfully finish a project - or at least bring it to a completed state - are constraints. Adding new features is great; maintaining them is a different ball game. Going back and documenting the features that you *just had* to add two months ago takes time and effort. And, being a person who insists on writing extremely verbose documentation or none at all, I end up either being tied down for days thoroughly documenting everything, or having a lot of undocumented code.

For that reason, for the graphing calculator that I chose to write in C# for my A-level Computing coursework, I forced myself to be heavy-handed. No, Tom, this graphing calculator doesn't need to support embedded HTML pages and animated .GIFs in annotations. By constraining yourself to what needs to be done, it's generally far easier to reach an acceptable level of completion quicker, while giving yourself time to add extras on afterward. This kind of pragmatism might seem blindingly obvious, but it's easy to let features creep in when you're working on a project by yourself.

Upon being given the chance to write my own software for a piece of coursework, I took the chance to write something that I've wanted to create for a long time. The coursework guidelines gave no limitations as to which UI frameworks should be used, which language you should work with, or the architecture that your project should adhere to. Naturally, I chose the language that I am most proficient in - C# - and settled on the framework which would allow me to get something working the fastest. WinForms.

## System.Windows.Forms

WinForms is a fairly thin API around the Windows API, much like its loose predecessor, MFC. This lends it absolutely no cross-platform compatibility whatsoever: Mono has only partial support for Windows Forms. However, one thing WinForms really excels at is rapid application development. If you need to get an interface for a small program done, and you need it done quickly, the drag-and-drop interface is excellent for the task.

<div style="text-align: center">
  <img alt="The drag-and-drop interface used to visually edit Windows Forms programs in Microsoft Visual Studio." src="{{ site.base_url }}/images/coursework/winforms1.png" /><br/>
  <span class="post-meta small">There are lots of controls available to use in Windows Forms - all of which look and feel native to the Windows UI.</span>
</div>

Creating an interface is literally a drag-and-drop operation - the interface is intuitive, accessible, and could be done by anyone[^4]. The designer draws heavy inspiration from the designer that comes with Visual Basic 6.0, and is similar to that of the older version of Borland Delphi.

<div style="text-align: center">
  <img alt="The drag-and-drop interface used to visually edit Windows Forms programs in Microsoft Visual Studio." src="{{ site.base_url }}/images/coursework/winforms2.png" /><br/>
  <span class="post-meta small">In about two minutes, you can create a dialog that looks sharp, resizes correctly and is accessible.</span>
</div>

With developers coming from C++ and MFC, it's easy to see why this was an attractive option. Indeed, before the release of [WPF](http://en.wikipedia.org/wiki/Windows_Presentation_Foundation), it was the only realistic option available to C# developers for creating a user interface. Still, this ease of use means it's easy to get a small program up and running in very little time at all.

However, large projects tend to start off as small projects, and maintaining large WinForms-based projects is a totally different story.

With WinForms being no more than an object-oriented layer over the Windows API, you have no constraints enforced, or architectures recommended, around which to design the program. While it is possible (and actually not too unpleasant) to create the forms entirely without using the designer, the code generation that the designer uses behind the scenes will create giant monolithic `.Designer.cs` files for the layout of the form, which are impossible to maintain for anyone who isn't using Visual Studio. Controls are all positioned with absolute co-ordinates on the page, with no structured layout used at all, meaning that the Forms designer is *needed* to get an idea of what the form looks like:

{% highlight csharp %}
this.panToolStripMenuItem.Image = global::Graphmatic.Properties.Resources.ArrowMove16;
this.panToolStripMenuItem.Name = "panToolStripMenuItem";
this.panToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.N)));
this.panToolStripMenuItem.Size = new System.Drawing.Size(173, 22);
this.panToolStripMenuItem.Text = "Pa&n";
{% endhighlight %}

Creating re-usable parts of code for a Forms application is possible but requires more effort than it should to do in order for it to be done correctly; even then, the end result is not pretty. This sort of design encourages a top-down approach to building projects, which has a habit of leading to badly-structured, poorly thought out programs. Design documents might seem like a lot of effort, but in this situation they've helped me quite a bit.

The event-driven design of WinForms means that the event handlers for controls on the form are, by default, all piled into the same class that displays the controls themselves (and, in a lot of cases, the state of the program).

<div style="text-align: center">
  <img alt="The main screen of my graphing calculator that I have written as my coursework project." src="{{ site.base_url }}/images/coursework/project1.png" /><br/>
  <span class="post-meta small">Interfaces with any considerable level of complexity quickly inflate to over a thousand lines of code... in one class.</span>
</div>

Frameworks such as WPF, on the other hand, strongly encourage you to abide by the Model-View-ViewModel architecture. This neatly separates the layout of the interface, the structure of the data being passed about, and the ViewModel, which acts to turn the raw data into something the UI can display, perhaps transforming the data in the process. Data binding in XAML does the talking between the View and the ViewModel.

The free reign that WinForms gives you in comparison to this encourages bad architectural choices early in the program, which are *much* harder to fix or clean up later on. I made the UI logic of the main window in my project more manageable with liberal use of partial classes, but that's a temporary solution to a glaring problem. From this experience, if you're thinking of using WinForms, then conform to a strict architectural pattern. If you do it from the beginning, then it should not be too difficult to write forms as the View component of an MVC- or MVVM-based application.

WF does support limited data binding on most controls, and for those that don't, it's also conceivable to roll your own with careful use of the validation events that WF provides. Do not be tempted to put more non-view or non-validation logic into the form than is absolutely necessary - this is easy to do, and will make your life (and the next developer's life) a pain.

<div style="text-align: center">
  <img alt="A screenshot of the data-binding that Windows Forms controls support." src="{{ site.base_url }}/images/coursework/winforms3.png" /><br/>
  <span class="post-meta small">If you're working with a database than data binding support comes pre-loaded with WinForms.</span>
</div>

At the time, the only reason I went with Windows Forms was because my coursework is not being marked on its maintainability - the project only needs to be completed and documented. The effort required to get used to WPF would have taken too long in the context of this project. Also, WPF seems to have a habit of making difficult things easy, and simple things extremely unintuitive[^3], and working around those quirks would have meant I would have spent most of the available time learning about the ins and outs WPF, rather than developing the project itself.

## System.Drawing and GDI+

Graphical drawing capabilities are a fairly intrinsic part of my project, with it being a graphical calculator. Luckily, the .NET framework sports a graphics system in the `System.Drawing` namespace which is fairly similar to the `java.awt.Graphics` class from which it was probably inspired. The system is a managed layer over the GDI+ API, which again limits portability to Windows, as the graphics device interface is another Windows-specific system.

The API that the .NET Framework provides isn't all that bad. It supports enough features to get most jobs done - enough to render the visual part of my graphing calculator.

<div style="text-align: center">
  <img alt="A screenshot of my graphing calculator being used to plot the Lambert W function." src="{{ site.base_url }}/images/coursework/project2.png" /><br/>
  <span class="post-meta small">2D drawing support exposed by GDI+ is quite feature-complete.</span>
</div>

Of course, with GDI+ being an unmanaged API, you need to be careful to free all resources that you use. This involves calling `Dispose()` on every GDI+ resource you create, or surrounding everything in `using()` clauses.

The downside of using GDI+ is the total lack of hardware acceleration. The graphing calculator noticeably slows down when you zoom in and out with a lot of content on the page - the plotted curves are being redrawn with marching squares each time. In fact, the entire page display gets fully redrawn each time any part of the page display changes. In hindsight, I probably would have opted forOpenGL or Direct2D instead of GDI+ for the page display, to avoid the speed overhead.

<div style="text-align: center">
  <img alt="A screenshot of the Windows Task Manager when redrawing a lot of visuals in the graphing calculator display." src="{{ site.base_url }}/images/coursework/project3.png" /><br/>
  <span class="post-meta small">The high CPU usage when redrawing, and particularly the amount of kernel time (in red), leads me to believe a lot of the slowdown is due to the context switching when dipping into the underlying GDI layer.</span>
</div>

However, compared to the convenient drawing methods that GDI+ provide, Direct2D and OpenGL both require a lot more development time to present the same visual effects; the OpenGL API is notoriously arcane (thanks, ARB). This again presents the problem of whether the speed-up in development time is a worthy trade off. For this coursework project, it undoubtably is. For a commercial product, however, not so much.

## Graphmatic

The coursework project (named *Graphmatic*) itself has, by and large, been successful. It plots essentially any implicit function that doesn't involve calculus or summation very well. Equations are entered in the style of a well-known scientific calculator with pretty-print *LaTeX*-esque display:

<div style="text-align: center">
  <img alt="The dialog used in Graphmatic for entering mathematical equations, with a strange equation entered into the dialog.." src="{{ site.base_url }}/images/coursework/project4.png" /><br/>
  <span class="post-meta small">You can enter the weirdest-looking equation you want...</span>
</div>

<div style="text-align: center">
  <img alt="The result of plotting the previous equation in the graph display." src="{{ site.base_url }}/images/coursework/project5.png" /><br/>
  <span class="post-meta small">...and the program will handle it fine.</span>
</div>

The plotting uses marching squares for any implicit equations. For everything else, the plotter falls back to plotting the value at every point along the axis and joining the dots, like most plotting programs. The program also handles data sets, too. For example, I can enter the Fibonacci sequence:

<div style="text-align: center">
  <img alt="The Fibonacci sequence entered into the data set editor (which resembles a spreadsheet editor.)" src="{{ site.base_url }}/images/coursework/project6.png" /><br/>
  <span class="post-meta small">Multivariate data sets are supported too - of course, only two variables can be plotted at any time.</span>
</div>

And, amongst other statistical functions, you can calculate the regression line fitting the data.

<div style="text-align: center">
  <img alt="The Fibonacci sequence, as entered before, plotted onto a graph - with a linear regression line, too." src="{{ site.base_url }}/images/coursework/project7.png" /><br/>
  <span class="post-meta small">Other statistical functions like PMCC, mean, covariance and such functions are also supported. The program has a fairly modular API for writing statistical functions, so with very few changes the program could support plugins, too.</span>
</div>

Last but not least, drawn and image annotations are also part of the package. It's certainly not equipped with Photoshop-grade drawing tools, but a pencil, a highlighter, an eraser and image support is all that should be needed for a demonstration. The program is designed for use in classrooms by teachers (as the coursework requires a specific end-user), so the Maths department at my college doubles up as my beta testing department, which is awfully convenient.

<div style="text-align: center">
  <img alt="The Fibonacci sequence plotted as shown previously, with some annotations added from within the program itself." src="{{ site.base_url }}/images/coursework/project8.png" /><br/>
  <span class="post-meta small">Unfortunately, if you want to resize more than one object at once, I'm afraid you're out of luck - sorry.</span>
</div>

There are some gotchas in the program. Most of these are either due to time constraints, or realising that a simple-sounding concept is much more involved to implement than I initially planned.

* Universal clipboard support. The only things that can be pasted into the program are image annotations. After trying to add support for the mixing of resources (those things on the left, like pages and data sets) between documents, I gave up after wrestling with the WinForms Keyboard class (which is an awfully thin wrapper around OLE object handling) and finding a non-ugly way of creating deep copies of resources.

* Undo and Redo. Seems simple enough in theory - maintain a stack of operations performed on the document, and push something onto it whenever you make a change. If you need to undo, pop something off the stack, and perform the reverse operation, and vice versa for redo. However, this would require access to a singleton class in every little corner of the program. I'm not sure which design pattern huge software suites like Office use for supporting these operations, but I'd sure like to know. Because of this, Graphmatic has no undo/redo support, which is perhaps the thing I'm least happy with.

* Somewhat clunky UI. Don't get me wrong - the interface works. However, you need to know the ins and outs of how data is stored in the document in order to use the interface most effectively, or you end up storing a lot of unused resources. Also, when you have a page open in the document, and you open another resource (such as an equation) and subsequently close the equation editor, the program still thinks the *equation* is open, not the page. Hence, if you were to delete the equation, the page editor will close, even though the page has not been deleted. Big projects must have user experience teams to work solely on problems like this, as simple things such as what I've described can often take a complete rework of the UI logic to fix.

Besides these fairly minor problems, the program works fine. For what it is, of course - it's a student coursework project, and at the end of the day it's not going to be commercially sold or anything.

One thing that has helped greatly has been the use of source control. I am the only developer working on this project, so it has not been strictly necessary. However, by forcing myself to use Git, I've learned about branches, merging and some of the more subtle features of DVCSes like Git, which is a handy skill to have. I've been using Github to host the project, and the issue/milestone system has also been very useful for keeping track of what needs to be done.

<div style="text-align: center">
  <img alt="The Github issue tracker which I have used religiously to manage the project." src="{{ site.base_url }}/images/coursework/project9.png" /><br/>
  <span class="post-meta small">No issues open... it's beautiful.</span>
</div>

After the coursework piece has been handed in and formally marked, which will be in June, I'm hoping to make the Github repository public and put the program under something like the BSD 3-Clause Licence. It's not badly written by any means, and the documentation is quite dense throughout the project, so there's no point *not* releasing it for the world to see. Ideally, I would have written unit tests with NUnit or something similar, but I fell prey to the WinForms mind-set early on, so the inversion of control is too patchy to reliably and consistently use automated testing.

Overall, creating Graphmatic has been a solid learning experience, and the things I have learned *not* to do with this project are lessons that I think can be applied to any engineering or development project.

[^3]: [http://loyc-etc.blogspot.co.uk/2011/07/why-wpf-sucks.html](http://loyc-etc.blogspot.co.uk/2011/07/why-wpf-sucks.html)
[^4]: As shown by the fact that even the dated Office macro system supports a bastardized edition of VB6 forms. [Look familiar?]({{ site.base_url }}/images/coursework/winforms4.png)
