ARCH=`uname -m`
TAG_NAME=`git describe --tags --abbrev=0`

APPDIR=appdir
DMGDIR=dmgdir/smk.app
EXE=super_mario_kart

os:
	@echo ${ARCH}

appimage:
	EXE=super_mario_kart
	# Setup
	mkdir -p ${APPDIR}
	cp -r assets LICENSE README.md ${EXE} assets/smk.desktop assets/smk.png ${APPDIR}
	# builder
	wget -q "https://github.com/linuxdeploy/linuxdeploy/releases/download/1-alpha-20240109-1/linuxdeploy-${ARCH}.AppImage"
	chmod a+x linuxdeploy-${ARCH}.AppImage
	# build AppImage
	./linuxdeploy-${ARCH}.AppImage --executable ${EXE} --appdir ${APPDIR} --output appimage --desktop-file appdir/smk.desktop --icon-file appdir/smk.png
	mv Super_Mario_Kart-${ARCH}.AppImage smk-lin-${ARCH}-${TAG_NAME}.AppImage

dmg:
	# Set BREW_PREFIX variable using shell command
	$(eval BREW_PREFIX := $(shell brew --prefix sfml))
	# Setup
	mkdir -p ${DMGDIR}/Contents/MacOS ${DMGDIR}/Contents/Resources ${DMGDIR}/Contents/libs
	cp assets/smk.command dmgdir/run.command
	cp assets/Info.plist ${DMGDIR}/Contents/Info.plist
	cp ${EXE} ${DMGDIR}/Contents/MacOS/smk
	cp -r assets ${DMGDIR}/Contents/Resources

	(cd ${DMGDIR}/Contents/MacOS && ln -s ../../Contents/Resources/assets assets)

	cp assets/smk.png ${DMGDIR}/Contents/Resources/AppIcon.png

	dylibbundler --no-codesign --create-dir --bundle-deps \
        --fix-file ${DMGDIR}/Contents/MacOS/smk \
        --dest-dir ${DMGDIR}/Contents/libs

	hdiutil create -size 10m -fs APFS -volname "smk" -srcfolder dmgdir -format SPARSE "smk-mac-${ARCH}-${TAG_NAME}.dmg"

tar.gz:
	tar -czf "smk-mac-${ARCH}-${TAG_NAME}.tar.gz" assets LICENSE README.md super_mario_kart

zip:
	zip -r "smk-win-${ARCH}-${TAG_NAME}.zip" assets LICENSE README.md openal32.dll super_mario_kart.exe

bin:
	rm -rf bin
	mkdir -p bin
	chmod -R 777 bin

mingw:	bin
	docker build . -f Dockerfile.mingw -t mingw
	docker run -t --rm -v ${PWD}:/tmp/wd -w/tmp/wd -t mingw bash -c "(cd src && make -f Makefile OS=mingw release) && cp /usr/i686-w64-mingw32/sys-root/mingw/bin/openal32.dll bin"
	cp bin/openal32.dll bin/super_mario_kart.exe .

clean:
	rm -rf ${APPDIR} ${DMGDIR} *.dmg *.AppImage *.exe *.dll *.zip bin