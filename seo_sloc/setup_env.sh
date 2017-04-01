#Check sudo
if [ $EUID ]; then
	echo "This script should be run using sudo or as the root user"
	exit 1
fi

echo "\nInstalling pip"
apt-get install python-pip
echo "DONE"

echo "\nInsalling dependency packages"
echo "\nRadon"
pip install radon
echo "ok"
echo "\nReportlab"
pip install reportlab
echo "ok"