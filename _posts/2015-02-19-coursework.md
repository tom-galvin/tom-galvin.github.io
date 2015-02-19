---
layout: post
title: Lessons learned from a successful project
date: 2015-02-19 22:13:36
summary: Some morsels of wisdom picked up about using WinForms and GDI+ in my A-level Computing coursework.
categories: blog dev
---
The feeling you get upon finishing a project is, without a doubt, one of the better parts of programming. I must admit that my started-to-completed ratio is shocking: I have many half-baked projects in several different languages and frameworks cluttering my hard-drive. A lot of these are due to time constraints, getting bored of the idea, or simply having the project run away from me - realising soon after starting that it's going to take a lot more effort to finish this than I had hoped.

I think the most important thing that you need in order to successfully finish a project - or at least bring it to a completed state - are constraints. Adding new features is great; maintaining them is a different ball game. Going back and documenting the features that you *just had* to add two months ago takes time and effort. And, being a person who insists on writing extremely verbose documentation, this isn't the most exciting thing ever.

For that reason, for the graphing calculator that I chose to write in C# for my A-level Computing coursework, I forced myself to be heavy-handed. No, Tom, this graphing calculator doesn't need to support embedded HTML pages and animated .GIFs in annotations. By constraining yourself to what needs to be done, it's generally far easier to reach a completed level quicker, while giving yourself time to add extras on afterward. This sort of pragmatism might seem blindingly obvious, but it's easy to let features creep in when you're working on a project by yourself.

Upon being given the chance to write my own software for a piece of coursework I took the chance to write something that I've wanted to create for a long time. The coursework guidelines gave no limitations as to which UI frameworks should be used, which language you should work with, or the architecture that your project should adhere to. Naturally, I chose the language that I am most proficient in - C# - and settled on the framework which would allow me to get something working the fastest. WinForms.

## System.Windows.Forms

WinForms is a fairly thin API around the Windows API, much like its loose predecessor, MFC. This lends it absolutely no cross-platform compatibility whatsoever: Mono has only partial support for Windows Forms. However, one thing WinForms really excels at is rapid application development. If you need to get an interface for a small program done, and you need it done quickly, the drag-and-drop interface is particularly alluring.

<div style="text-align: center">
  <img alt="The drag-and-drop interface used to visually edit Windows Forms programs in Microsoft Visual Studio." src="{{ site.base_url }}/images/coursework/winforms1.png" /><br/>
  <span class="post-meta small">There are lots of controls available to use in Windows Forms - all of which look and feel native to the Windows UI.</span>
</div>

Creating an interface is literally a drag-and-drop operation. The designer draws heavy inspiration from the designer that comes with Visual Basic 6.0 and is similar to that of the older version of Borland Delphi.

<div style="text-align: center">
  <img alt="The drag-and-drop interface used to visually edit Windows Forms programs in Microsoft Visual Studio." src="{{ site.base_url }}/images/coursework/winforms2.png" /><br/>
  <span class="post-meta small">In about two minutes, you can create a dialog that looks sharp, resizes correctly and is accessible.</span>
</div>

With developers coming from C++ and MFC, it's easy to see why this was an attractive option. (Indeed, before the release of [WPF](http://en.wikipedia.org/wiki/Windows_Presentation_Foundation), it was the only option available to C# developers for creating a user interface.) This ease of use means it's easy to get a small program up and running in very little time at all. However, large projects tend to start off as small projects, and maintaining large WinForms-based projects is a totally different story.

With WinForms being no more than an object-oriented layer over the Windows API, you have no constraints enforced or architectures recommended to you around which to design the program. While it is possible (and actually not too unpleasant) to write the code-behind for the forms manually, the code generation for the designer generates giant monolithic `.Designer.cs` files for the layout of the form. This sort of design encourages a top-down approach to building projects. I tend to find, however, that user interfaces are far easier maintained when written from the bottom up.

The event-driven design of WinForms means that the event handlers for controls on the form are all piled into the same class that displays the controls themselves - and, in a lot of cases, the state of the program.

<div style="text-align: center">
  <img alt="The main screen of my graphing calculator that I have written as my coursework project." src="{{ site.base_url }}/images/coursework/project1.png" /><br/>
  <span class="post-meta small">Interfaces with any considerable level of complexity quickly inflate to over a thousand lines of code... in one class.</span>
</div>

Frameworks such as WPF, on the other hand, *force* you to abide by the Model-View-ViewModel architecture. This neatly separates the layout of the interface, the structure of the data being passed about, and the ViewModel, which acts to turn the raw data into something the UI can show intuitively, perhaps transforming the data in the process. Data binding in XAML does the talking between the View and the ViewModel.

The free reign that WinForms gives you in comparison to this encourages bad architectural choices early in the program, which are *much* harder to refactor later on. I made the UI logic of the main window in my project more manageable with liberal use of partial classes, but that's a temporary solution to a glaring problem. From this experience, if you're thinking of using WinForms, I have this to say:

* Don't use WinForms. Not only is WPF far more modern and maintainable, it's also cross-platform. You're able to use the same code on the Windows Desktop, the Windows Store, and Windows Phone. You also have hardware acceleration, which WinForms/GDI+ does not afford - more on that soon.

* If you *absolutely need* to use WinForms, then conform to a strict architectural pattern. If you do it from the beginning, then it should not be too difficult to write forms as the View component of an MVC- or MVVM-based application. WF does support limited data binding on most controls, and for those that don't it's conceivable to roll your own with careful use of the validation events that WF provides. Do not be tempted to put non-view or non-validation logic into the form - this is a dangerous path to tread.

The only reason I went with Windows Forms in the first place is the somewhat-steep learning curve of XAML. I have never really looked too hard at XAML or gave it a fair opportunity. I think I need to at this point, as Windows Forms is a legacy platform.

***to be continued***