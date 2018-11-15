## Homework 4
<p><strong>Description</strong></p>
<p>The purpose of this project is to get you started doing more sophisticated hybrid programming on a machine like Beocat.</p>
<p><strong>Task(s)</strong></p>
<p>Write a Hybrid MPI/OpenMP program to complete problems 1-2. Run each program on Beocat using a significant amount of compute time. For example, you could use about 30s of compute time per problem. Compare the runtimes as you increase the number of threads per MPI program (1, 2, 4, 8). Perform the tests on up to 16 cores. How do the results compare to each other? Are the hybrid versions faster?</p>
<ol>
<li>Write an MPI program to perform numerical integration on something close to Easom’s function -</li>
</ol>
<p>f(x, y) = -cos(x)*sin(y)*exp( -((x - PI)*(x - PI) + (y - PI)*(y - PI)) )</p>
<p>E.g., your core loop could be something like</p>
<p>     for(i = loopStart; i &lt; loopStart+workToDo ; i++)</p>
<p>         for(j = 0; j &lt; endYdir; j++)</p>
<p>                 volume += h*h*f(x + i*h, y + j*h);</p>
<p>where <em>h</em> is a really small number, like 0.00001 (the size of your rectangle), and <em>loopStart</em> is the start of your section of the work to calculate the overall volume defined by the function.</p>
<p>Assume that the starting and ending points for both x and y are provided as command line arguments. Your program must make use of the MPI_Reduce function.</p>
<p> </p>
<ol start="2">
<li>Assume that you wish to test the performance of several numerical optimization methods on a particular function</li>
</ol>
<p>f(x) = cos(x)+(pow(fabs(6.0-x), 2.0/15.0))+2*(pow(fabs(5.0-x), 4.0/35.0))</p>
<p>Write an MPI program that will broadcast the starting and ending locations for x that will be used to analyze this function. You may assume that one program will be used. This program will use a Monte-Carlo method to analyze the function (i.e generate a whole bunch of points within the range given at the command line and evaluate them to find the minimum). Be sure to print the resulting minimum.</p>
<p> </p>
<p>Plot the CPU time expended by the various versions of the program running with 1, 2, 4, 8, and 16 threads total (feel free to combine these into one graph). Spread your MPI processes across multiple machines (I’d suggest 1, 2, &amp; 4). Note that the x axis of your plot should be threads used, and the y-axis of your plot should be time expended in seconds. Discuss the results. Are there any race conditions? How much communication (in terms of # of messages and bytes/message) is there per variant?</p>
<p><strong>Resources</strong></p>
<p>MPI - <a href="https://computing.llnl.gov/tutorials/mpi/">https://computing.llnl.gov/tutorials/mpi/</a></p>
<p>Hybrid programming - <a href="https://docs.loni.org/wiki/Introduction_to_Programming_Hybrid_Applications_Using_OpenMP_and_MPI">https://docs.loni.org/wiki/Introduction_to_Programming_Hybrid_Applications_Using_OpenMP_and_MPI</a></p>
<p>  </p>
<p> </p>
<p>For help using the Beocat scheduler and its command lines, see the general help page</p>
<p>                <span><a href="https://support.beocat.ksu.edu/BeocatDocs/index.php/Main_Page">https://support.beocat.ksu.edu/BeocatDocs/index.php/Main_Page</a></span></p>
<p>and the scheduler help page</p>
<p>                <span><a href="https://support.beocat.ksu.edu/BeocatDocs/index.php/SGEBasics">https://support.beocat.ksu.edu/BeocatDocs/index.php/SGEBasics</a></span></p>
<p>Compute node specifications are at</p>
<p>                <span><a href="https://support.beocat.ksu.edu/BeocatDocs/index.php/Compute_Nodes">https://support.beocat.ksu.edu/BeocatDocs/index.php/Compute_Nodes</a></span></p>
<p> </p>
<p>You will probably need to install a shell program on your Windows machine – I use PuTTY, and  program to transfer files back and forth (I use WinSCP, but other options are fine). Linux and Mac OS have terminal and file transfer programs installed by default.</p>
<p><strong>Submission instructions</strong></p>
<p>Submit a PDF which contains your analysis, and code and your various controlling shell scripts as separate uploads. Submit these via Canvas. Grading will be split – 75% for the correctness and performance of your implementation (including use of shell scripts), 25% for your performance analysis (probably 1-2 pages, including graphs but excluding appendices, assuming a reasonably compact formatting scheme).</p></div>
