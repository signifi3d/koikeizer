# koikeizer

Inspired by artist Kensuke Koike. This little command line app makes use of the simplistic CImg library to basically cut images into vertical and horizontal strips and either use the strips to make smaller facsimilies of the images or just swap them around in-place.

Basically it's what Koike does in [this](https://www.youtube.com/watch?v=f1fXCRtSUWU) video with a pasta cutter.

Options are as follows:

-r n

&nbsp;&nbsp;&nbsp;&nbsp;Make n horizontal cuts. Default is 10.
  
-v n

&nbsp;&nbsp;&nbsp;&nbsp;Make n vertical cuts. Default is 10.

-o filepath

&nbsp;&nbsp;&nbsp;&nbsp;Output the result to a file. Omitted displays the result in a window.

-i

&nbsp;&nbsp;&nbsp;&nbsp;In-place swapping.

-s

&nbsp;&nbsp;&nbsp;&nbsp;Split image swapping. (Default)
