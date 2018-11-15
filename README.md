# concurrent-systems
This repo is for my coursework in CIS 625/Concurrent Systems at KSU.

**PLEASE DO NOT COPY WITHOUT PERMISSION**
## Homework 0
<p><strong>Description</strong></p>
<p>The purpose of this project is to get you used to submitting jobs to Beocat using the scheduler, for multiple numbers of machines (nodes) to complete a job. This is complementary to our lecture Friday, where you will learn how to do exactly this.</p>
<p><strong>Task(s)</strong></p>
<p>Execute the “print the name of this node” program which you were given in three ways:</p>
<ol>
<li>1 copy, 1 node</li>
<li>5 copies, 1 node</li>
<li>2 copies, 2 different nodes</li>
</ol>
<p>The program can be a simple shell script like</p>
<p>     #!/bin/bash</p>
<p>     echo "The name of the node is `hostname`."</p>
<p>First, you need to get an account by visiting <u><a href="https://account.beocat.ksu.edu/">https://account.beocat.ksu.edu/</a></u> and filling out the form. In most cases approval for the account will be granted in less than one business day, and sometimes much sooner. When your account has been approved, you will be added to our <u><a href="https://support.beocat.ksu.edu/BeocatDocs/index.php/LISTSERV">LISTSERV</a></u>, where we announce any changes, maintenance periods, or other issues.</p>
<p>Once you have an account, you can access Beocat via SSH and can transfer files in or out via SCP or SFTP (or <u><a href="https://www.globus.org/">Globus Connect</a></u> using the endpoint <em>beocat#beocat</em>). If you don't know what those are, please see our <u><a href="https://support.beocat.ksu.edu/BeocatDocs/index.php/LinuxBasics">LinuxBasics</a></u> page. If you are familiar with these, connect your client to headnode.beocat.ksu.edu and use your K-State eID credentials to login.</p>
<p>As mentioned above, we use Slurm for job submission and scheduling. If you've never worked with a batch-queueing system before, submitting a job is different than running on a standalone Linux machine. Please see our <u><a href="https://support.beocat.ksu.edu/BeocatDocs/index.php/SlurmBasics">SlurmBasics</a></u> page for an introduction on how to submit your first job. If you are already familiar with Slurm, we also have an <u><a href="https://support.beocat.ksu.edu/BeocatDocs/index.php/AdvancedSlurm">AdvancedSlurm</a></u> page where we can adjust the fine-tuning. If you're new to HPC, we highly recommend the <u><a href="http://www.oscer.ou.edu/education.php">Supercomputing in Plain English (SiPE)</a></u> series by OU. In particular, the older course's streaming videos are an excellent resource, even if you do not complete the exercises.</p>
<p> </p>
<p><strong>Resources</strong></p>
<p>For help using the Beocat scheduler and its command lines, see the general help page</p>
<p>                <span>https://support.beocat.ksu.edu/BeocatDocs/index.php/Main_Page</span></p>
<p>and the scheduler help page</p>
<p>                <span>https://support.beocat.ksu.edu/BeocatDocs/index.php/SlurmBasics</span></p>
<p> </p>
<p>You will probably need to install a shell program on your Windows machine – I use PuTTY, and a program to transfer files back and forth (I use WinSCP, but other options are fine). Linux and Mac OS have terminal and file transfer programs installed by default.</p>
<p><strong>Submission instructions</strong></p>
<p>Take a screen shot of the output from each of the three runs (you will probably end up using programs like grep and more) on a single terminal window screen (this will require a little careful practice to arrange, I suspect). Submit this image via Canvas.</p></div>

## Homework 1
<p><strong>Description</strong></p>
<p>The purpose of this project is to get you used learn how to do a performance evaluation on a machine like Beocat.</p>
<p><strong>Task(s)</strong></p>
<p>Your first task is to take an existing program and indicate how the performance improves through using using two standard techniques – tiling and loop unrolling – in this serial code. In my directory on Beocat ~dan/625, there is a program called pt0.c, which creates a large array of characters and then counts them. Make yourself a copy and modify this code (in particular, the count_array() function) into two variants (pt0-tiled.c and pt0-unrolled.c). Your second task is to do a performance evaluation across a range of array sizes to see how the various versions match up in terms of run times, CPU efficiency, memory utilization, etc. You’ll want to keep the machines constant, so use the ‘-q \*@@elves’ flag to confine your jobs to only the ‘elf’ class nodes.</p>
<p>I’ve provided code in the file mytime.c to illustrate how to time portions of code. Note that it also illustrates how to retrieve data from the program’s environment (in this case, SLURM_NTASKS, which is the number of cores you have). Also note – and <strong>this is important</strong> – the format of the output makes it easy to extract the data (using the ‘grep’ command) into a .csv file, which can be opened directly.</p>
<p>So if you wanted to be efficient about things, you would modify the various programs to accept the size of the array to be tested as an input argument, then use a script like the 625/mass_sbatch.sh to submit a bunch of jobs simultaneously, and then a ‘grep’ into a .csv file to quickly graph the output in Excel or a similar tool.</p>
<p>Read the discussion of performance analysis on Canvas, and make sure you discuss the applicable elements. You should run your jobs multiple times per data point and then average them to help smooth out individual variations. You should make sure you discuss how you selected the block size for your tiled implementation and the degree of loop unrolling (a graph to prove your point as to which was optimal would be great), and how you chose the array dimensions to do a reasonable evaluation of the algorithms’ performance.</p>
<p><strong>Resources</strong></p>
<p>Tiling - <span><a href="https://en.wikipedia.org/wiki/Loop_nest_optimization">https://en.wikipedia.org/wiki/Loop_nest_optimization</a></span></p>
<p>Loop unrolling - <span><a href="https://en.wikipedia.org/wiki/Loop_unrolling">https://en.wikipedia.org/wiki/Loop_unrolling</a></span></p>
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
<p>Submit a PDF which contains your analysis, and a copy of the two versions of your code and your various controlling shell scripts as supplementary files. Submit this via Canvas. Grading will be split – 50% for the correctness of your implementation (including use of shell scripts), 50% for your performance analysis (probably 2-3 pages, including graphs but excluding appendices, assuming a reasonably compact formatting scheme).</p></div>

## Homework 2
<p><strong>Description</strong></p>
<p>The purpose of this project is to get you started doing parallel programming on a machine like Beocat.</p>
<p><strong>Task(s)</strong></p>
<p>Your first task is to take an existing program and indicate how the performance improves through using using two standard techniques – pthreads and OpenMP – to parallelize this serial code. Your second task is to do a performance evaluation across a range of iterations to see how the various versions match up in terms of run times, CPU efficiency, memory utilization, etc. You’ll want to keep the machines constant, so use the flag for sbatch to confine your jobs to only the ‘elf’ class nodes.</p>
<p>Parallelize the following code using OpenMP parallel and reduction directives. Ensure that your program prints the output and tracks and prints the time expended by the program.<br><br>const int NUM_ITER = 100000000;<br>int i;<br>double sum = 0.0, x = 0.0;<br>double st = 1.0/((double) NUM_ITER);<br>for(i = 0; i &lt; NUM_ITER; i++)<br>{<br>  x = (i + 0.25)*st;<br>  sum += 4.0/(x*x+1);<br>}</p>
<p>Plot the CPU time expended by the serial version of the program and by running the program with 2, 4, 8, and 16 threads for both the pthreads and OpenMP versions (feel free to combine these into one graph). Note that the x axis of your plot should be threads used, and the y-axis of your plot should be time expended in seconds. Discuss the results. Are there any race conditions?</p>
<p><strong>Resources</strong></p>
<p>Pthreads - <span><a href="https://computing.llnl.gov/tutorials/pthreads/">https://computing.llnl.gov/tutorials/pthreads/</a></span>  </p>
<p>OpenMP - <span><a href="https://computing.llnl.gov/tutorials/openMP/">https://computing.llnl.gov/tutorials/openMP/</a></span>  </p>
<p> </p>
<p>For help using the Beocat scheduler and its command lines, see the general help page</p>
<p>                <span><a href="https://support.beocat.ksu.edu/BeocatDocs/index.php/Main_Page">https://support.beocat.ksu.edu/BeocatDocs/index.php/Main_Page</a></span></p>
<p> </p>
<p> </p>
<p>Compute node specifications are at</p>
<p>                <span><a href="https://support.beocat.ksu.edu/BeocatDocs/index.php/Compute_Nodes">https://support.beocat.ksu.edu/BeocatDocs/index.php/Compute_Nodes</a></span></p>
<p> </p>
<p>You will probably need to install a shell program on your Windows machine – I use PuTTY, and  program to transfer files back and forth (I use WinSCP, but other options are fine). Linux and Mac OS have terminal and file transfer programs installed by default.</p>
<p><strong>Submission instructions</strong></p>
<p>Submit a PDF which contains your analysis and a copy of the two versions of your code and your various controlling shell scripts as additional files. Submit this via Canvas. Grading will be split – 75% for the correctness and performance of your implementation (including use of shell scripts), 25% for your performance analysis (probably 1-2 pages, including graphs but excluding appendices, assuming a reasonably compact formatting scheme).</p></div>

## Homework 3
<p><strong>Description</strong></p>
<p>The purpose of this project is to get you started doing distributed programming on a machine like Beocat.</p>
<p><strong>Tasks</strong></p>
<p>A friend of mine uses a list of 50,000 terms and checks them against a list of 1M text strings. On his machine, which has 32 cores and 128GB RAM, this takes 17 minutes. I think we can do much better than this. On Beocat there is a moderately large (wiki_dump.txt, 1.7GB) file containing approximately 1M Wikipedia entries, 1 entry per line. There is also a list of 50,000 words (keywords.txt, extracted from a common cracking dictionary). You can find the files in /homes/dan/625 on Beocat. Use these files – do not make your own copies. There is also a sample implementation using OpenMP (find_keys.c).</p>
<p>Read the files into memory, check for matches, and then print out an alphabetized list of words which appeared in the text strings, with their indices (by line number). Look for each word as substring – you do not have to worry about whether it is a whole word or not. You may assume that all words are entirely in lowercase. You do not need to list words which do not have a match. E.g.</p>
<p> </p>
<p>                abba: 45, 56, 30000, 999999</p>
<p>                bob: 1, 5, 200, 3333</p>
<p>                etc.</p>
<p> </p>
<p>Your output should be identical for all versions and configurations of your code<strong>.</strong></p>
<p><strong>Mechanics</strong></p>
<p>Your first task is to implement your solution using MPI. Your second task is to do a performance evaluation across a range of input sizes and core counts to see how the various versions match up in terms of run times, CPU efficiency, memory utilization, etc. You’ll want to keep the machines constant, so use the ‘-q \*@@elves’ flag to qsub confine your jobs to only the ‘elf’ class nodes. Use a reasonable number of cores  – up to 64 on Beocat. Show how performance differs (if it does) across multiple machines vs. a single machine (e.g., 4 cores on 2 nodes vs. 8 cores on 1 node; you will only be able to do this up through 16 cores).</p>
<p>Graph your performance results. Discuss them. Are there any race conditions? How do you handle synchronization between processes? How much communication do you do, and are you making any attempts to optimize this? Why or why not?</p>
<p>WARNING: The 1 core/1M data elements version of the code can take 24 hrs to run, so start early!</p>
<p><strong>Resources</strong></p>
<p>Pthreads - <span><a href="https://computing.llnl.gov/tutorials/pthreads/">https://computing.llnl.gov/tutorials/pthreads/</a></span>  </p>
<p>OpenMP - <span><a href="https://computing.llnl.gov/tutorials/openMP/">https://computing.llnl.gov/tutorials/openMP/</a></span>  </p>
<p> </p>
<p>You will probably need to install a shell program on your Windows machine – I use PuTTY, and  program to transfer files back and forth (I use WinSCP, but other options are fine). Linux and Mac OS have terminal and file transfer programs installed by default.</p>
<p><strong>Submission instructions</strong></p>
<p>Submit a PDF which contains your analysis and separately upload copies of your code and your various controlling shell scripts. Submit this via Canvas. Grading will be split – 75% for the correctness and performance of your implementation (including use of shell scripts), 25% for your performance analysis (probably 2-3 pages, including graphs, assuming a reasonably compact formatting scheme).</p></div>

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
