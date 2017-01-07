#i3

This fork of i3 reforms certain functions of i3bar. In doing so, it removes
some features, and adds several. These are listed below.

##Features

###Borders

i3bar, by default, has a thin border going around itself. This border makes it
difficult to perform certain tricks with color. i3bar normally contains a
constant to adjust the size of this border, and therefore allows its removal by
setting the constant to zero. This option can only be changed by recompiling
(rather than configuration through .config/i3/conf), so here we are.

Rather than continue to inject this constant into every further adjustment,
they have all been made assuming a border of zero. 

###Width Control

i3bar will normally use only as much space as is needed to display your blocks.
Blocks can change the width they consume in two ways: first, they might set
min_width, specifying the width below which they should not drop. Equivalently,
they might pad themselves with whitespace characters, whose width will be
factored into their total width.

Since the whole bar will be filled in, regardless of whether something gets
put their, I think i3bar should use the full bar. Width control as described
previously was only done by the block. Since blocks don't know the total width
they have to fill, they cannot reliably fill it. A new option can then be set
by blocks: width. If set to a positive integer, it describes the number of 'M's
the block should consume (including separator space). If set to zero, it
indicates that the block should have variable width. If more space is available,
variable width blocks get more space. Space not taken up by fixed width blocks
is divided evenly among variable width blocks. 

This new form of width means that the two width setting methods previously
described - min_width and full_text - no longer control the width. 

###Powerline Divisions

Powerline is a vim plugin that alters the vim statusline to be more powerful and
pretty. It achieves prettiness through use of color, and by dividing everything
with arrows. I thought powerline looked nice, so I decided to copy it's look in
i3bar. In order to do so, one new option can be set by blocks, and a bunch of
other options are ignored. That option is 'above'. If a block is 'above' the
next block, it will be render with an arrow pointing into that block (unless
no_separator is set). Otherwise, the next block will have an arrow pointing into
the it (even if no separator is set). A block 'above' another will be drawn
after the lower one, and so has a higher z-index than the lower one.

The ignored options are those pertaining to separators, besides no_separator.
Specifically, separator, separator_block_width, and perhaps others. 

###Fill

A great deal many things a person might want to display on an i3bar are
percentages. E.g. volume, battery use, wifi strength. Fill describes a system to
make a better display for these percentages. Blocks can send the fill option as
a number between 1 and 100, describing the percentage thereof. Alternatively,
any full_text containing a number directly before a percent sign will be parsed
as a fill percentage. Blocks should also send a color in the 'fill_color' option. If
both fill and fill_color are set, then fill_color will be used like a second
background, filling a percentage of the width pertaining to the percentage
specified. 

##Use

No doubt many i3bar children easily support adding the necessary options to take
advantage many of these features. i3blocks allows the addition of options by
changing one line in a header file. However, more complex modifications are
required to fully realize the potential of width control. The modifications
remove support for automatic setting of width based on the width of text. The
thinking is that this is better controlled by the child process, since most
blocks will want a certain amount of padding, and there is no system to inform
i3bar of your desired padding. The old i3bar supported padding control though
whitespace on the full_text. However, this requires configuration of your child
process to do anyways, so I thought you might as well modify your child to set
the width explicitly. 


i3status makes it quite difficult to add new properties, requiring them to be
individually configured for each block type. Moreover, in it's default state, it
doesn't support the current full wealth of i3bars options (eg background).
Furthermore, i3status is complex enough that adding the width modifications
described above would be quite a chore.


##Example

i3bar is fully dependant on it's child process. Following is an image of an
example configuration. This configuration  would be described in detail at
syrrim/i3blocks. 

![example](screenie.png)


##Upstream

This is a fork of i3/i3. The majority of the source code, including anything
outside i3bar, comes from there. Patches pertaining to the features described
above, or which analysis of the commit history has otherwise lain at my feet,
might be submitted here. Otherwise, they should probably be brought to the
attention of mainline i3. 
