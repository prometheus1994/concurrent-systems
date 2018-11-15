# concurrent-systems
This repo is for my coursework in CIS 625/Concurrent Systems at KSU.

**PLEASE DO NOT COPY WITHOUT PERMISSION**
## Homework 1
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
