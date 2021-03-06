# bin/bash
export PROGNAME=game-life-screensaver
export VERSION=1.0.0
export MAIL=medved_cool@mail.ru
export KEYWORD=_C
export SRC=`(find ../ -name '*.c' -printf '../%P ')`
export GLADE=`(find ../ -name '*.glade' -printf '../%P ')`




xgettext					 	--package-name=$PROGNAME --package-version=$VERSION --msgid-bugs-address=$MAIL --i --from-code=UTF-8 --output=$PROGNAME.pot $GLADE
xgettext -j --keyword=$KEYWORD	--package-name=$PROGNAME --package-version=$VERSION --msgid-bugs-address=$MAIL --i --from-code=UTF-8 --output=$PROGNAME.pot $SRC

if [ -f ru.po ];
then
	msgmerge --update ru.po $PROGNAME.pot
else
	msginit --no-translator --locale=ru_RU.utf8 --input=$PROGNAME.pot --output-file=ru.po
fi

if [ -f en_US.po ];
then
	msgmerge --update en_US.po $PROGNAME.pot
else
	msginit --no-translator --locale=en_US.utf8 --input=$PROGNAME.pot --output-file=en_US.po
fi
