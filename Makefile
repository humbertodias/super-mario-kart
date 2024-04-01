TAG_NAME=`git describe --tags --abbrev=0`

APPDIR=appdir
DMGDIR=dmgdir/smk.app
EXE=super_mario_kart

OS_TYPE := unknown
ifeq ($(OS),Windows_NT)
    OS_TYPE := windows
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		ARCH := x64
	else ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		ARCH := x86
	endif
else
	ARCH=`uname -m`
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        OS_TYPE := linux
    else ifeq ($(UNAME_S),Darwin)
        OS_TYPE := mac
    endif
endif

all:
	cd src && make

os:
	@echo ${OS_TYPE} - ${ARCH}

appimage:
	rm -rf ${APPDIR}
	mkdir -p ${APPDIR}
	cp -r assets LICENSE README.md bin/${EXE} assets/smk.desktop assets/smk.png ${APPDIR}
	wget -q "https://github.com/linuxdeploy/linuxdeploy/releases/download/1-alpha-20240109-1/linuxdeploy-${ARCH}.AppImage"
	chmod a+x linuxdeploy-${ARCH}.AppImage
	./linuxdeploy-${ARCH}.AppImage --executable appdir/${EXE} --appdir ${APPDIR} --output appimage --desktop-file appdir/smk.desktop --icon-file appdir/smk.png
	mv Super_Mario_Kart-${ARCH}.AppImage smk-lin-${ARCH}-${TAG_NAME}.AppImage

dmg:
	$(eval BREW_PREFIX := $(shell brew --prefix sfml))
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

	hdiutil create -size 50m -fs APFS -volname "smk" -srcfolder dmgdir -format SPARSE "smk-mac-${ARCH}-${TAG_NAME}.dmg"

tar.gz:
	tar -czf "smk-mac-${ARCH}-${TAG_NAME}.tar.gz" assets LICENSE README.md bin/super_mario_kart

zip:
	zip -r "smk-win-${ARCH}-${TAG_NAME}.zip" assets LICENSE README.md openal32.dll bin/super_mario_kart.exe

bin:
	rm -rf bin && mkdir -p bin && chmod -R 777 bin

release-mingw:	bin
	docker build . -f Dockerfile.mingw -t sfml-mingw
	docker run -t --rm -v ${PWD}:/tmp/wd -w/tmp/wd -t sfml-mingw bash -c "(cd src && make OS=Mingw release) && cp /usr/i686-w64-mingw32/sys-root/mingw/bin/openal32.dll bin"
	cp bin/openal32.dll bin/super_mario_kart.exe .

release-linux:	bin
	docker build . -f Dockerfile.linux -t sfml-linux
	docker run -t --rm -v ${PWD}:/tmp/wd -w/tmp/wd --privileged -t sfml-linux bash -c "(cd src && make OS=Linux release) && make appimage"

release-mac:	bin
	(cd src && make OS=Darwin release) && make dmg

clean:
	rm -rf ${APPDIR} ${DMGDIR} ${EXE} *.dmg *.dmg.sparseimage *.AppImage *.exe *.dll *.zip bin
	cd src && make clean