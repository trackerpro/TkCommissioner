export QTDIR=/opt/cmssw/shifter/erik/tmp/tmp/qt/qtinstall
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/opt/xdaq/lib:/usr/lib64
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$QTDIR/lib:$LD_LIBRARY_PATH
export PATH=$QTDIR/bin:$PATH
