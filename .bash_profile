alias lab3='cd /home/j6bui/lab3/lab3/src'
export TWIBBLER_PORT=9873
alias ts="${LAB2}/src/tribbler_server sysnet89.sysnet.ucsd.edu 7070 ${TWIBBLER_PORT}"
alias tc="${LAB2}/src/tribbler_client localhost ${TWIBBLER_PORT}"
export LD_LIBRARY_PATH=/usr/local/lib
export JAVA_HOME=/usr/lib/jvm/java-6-sun
export HADOOP_PATH=/classes/cse223b/sp13/labs/lab1/hadoop
export INPUT_PATH=/classes/cse223b/sp13/labs/lab1/input
export USER=`whoami`
unalias fs &> /dev/null
alias fs="hadoop fs"

alias qr='qsub ./run.sh'
alias qs='qstat -u bui'

alias up='cd ..'
alias up2='cd ../..'
alias up3='cd ../../..'
alias up4='cd ../../../..'
alias up5='cd ../../../../..'
alias up6='cd ../../../../../..'

cl ()
{
    cd $1
    ls
}

if [ "`hostname`" == 'jbu-laptop' ]
then
        export hh=/home/jbu/hadoop_local_install/hadoop-1.0.4
elif [[ "`hostname`" == "gordon"* ]]
then
        export hh=/opt/hadoop
elif [[ "`hostname`" == "sysnet"* ]]
then
        export hh=/classes/cse223b/sp13/labs/lab1/hadoop
else
        export hh=/opt/hadoop
fi

alias gordon='ssh bui@gordon.sdsc.edu'
alias hobo='ssh j6bui@hobo.sysnet.ucsd.edu'
alias sysnet='ssh j6bui@sysnet74.sysnet.ucsd.edu'

