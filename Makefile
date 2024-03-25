ARCH=`uname -m`
TAG_NAME=`git describe --tags --abbrev=0`

APPDIR=appdir
DMGDIR=smk.app
EXE=super_mario_kart

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
	mv Super_Mario_Kart-${ARCH}.AppImage smk-${ARCH}-${TAG_NAME}.AppImage

dmg:
	# Set BREW_PREFIX variable using shell command
	$(eval BREW_PREFIX := $(shell brew --prefix sfml))
	# Setup
	mkdir -p ${DMGDIR}/Contents/MacOS ${DMGDIR}/Contents/Resources ${DMGDIR}/Contents/Frameworks
	cp assets/Info.plist ${DMGDIR}/Contents/Info.plist
	cp ${EXE} ${DMGDIR}/Contents/MacOS
	cp -r assets ${DMGDIR}/Contents/Resources

	(cd ${DMGDIR}/Contents/MacOS && ln -s ../../Contents/Resources/assets assets)

	cp assets/smk.png ${DMGDIR}/Contents/Resources/AppIcon.png
	cp -L ${BREW_PREFIX}/lib/libsfml-{audio,graphics,window,system}.dylib ${DMGDIR}/Contents/Frameworks
	# TODO - Review this
	# install_name_tool -change ${BREW_PREFIX}/lib/libsfml-audio.2.6.dylib "@executable_path/../Frameworks/libsfml-audio.dylib" ${DMGDIR}/Contents/MacOS/${EXE}
	# install_name_tool -change ${BREW_PREFIX}/lib/libsfml-graphics.2.6.dylib "@executable_path/../Frameworks/libsfml-graphics.dylib" ${DMGDIR}/Contents/MacOS/${EXE}
	# install_name_tool -change ${BREW_PREFIX}/lib/libsfml-window.2.6.dylib "@executable_path/../Frameworks/libsfml-window.dylib" ${DMGDIR}/Contents/MacOS/${EXE}
	# install_name_tool -change ${BREW_PREFIX}/lib/libsfml-system.2.6.dylib "@executable_path/../Frameworks/libsfml-audio.dylib" ${DMGDIR}/Contents/MacOS/${EXE}
	hdiutil create -size 500m -fs APFS -volname "smk" -srcfolder ${DMGDIR} "smk-${ARCH}-${TAG_NAME}.dmg"

tar.gz:
	tar -czf "smk-mac-${ARCH}-${TAG_NAME}.tar.gz" assets LICENSE README.md super_mario_kart

clean:
	rm -rf ${APPDIR} ${DMGDIR} *.dmg *.AppImage