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
