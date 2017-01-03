for f in *.plantuml ; do java -jar "/home/andrii/git/plantuml.jar" "$f" ; done
for f in *.png ; do mv "$f" "assets" ; done
