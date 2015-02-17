#set the identification names for the frameworks using the install_name_tool -id
install_name_tool \
	-id @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore \
	SensPrecOptimizer.app/Contents/Frameworks/QtCore.framework/Versions/5/QtCore

install_name_tool \
	-id @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui \
	SensPrecOptimizer.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui

install_name_tool \
	-id @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets \
	SensPrecOptimizer.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets

install_name_tool \
	-id @executable_path/../Frameworks/OpenGL.framework/Versions/A/OpenGL \
	SensPrecOptimizer.app/Contents/Frameworks/OpenGL.framework/Versions/A/OpenGL

install_name_tool \
	-id @executable_path/../Frameworks/AGL.framework/Versions/A/AGL \
	SensPrecOptimizer.app/Contents/Frameworks/AGL.framework/Versions/A/AGL

install_name_tool \
	-id @executable_path/../Frameworks/libboost_filesystem-mt.dylib \
	SensPrecOptimizer.app/Contents/Frameworks/libboost_filesystem-mt.dylib

install_name_tool \
	-id @executable_path/../Frameworks/libboost_system-mt.dylib \
	SensPrecOptimizer.app/Contents/Frameworks/libboost_system-mt.dylib

install_name_tool \
	-id @executable_path/../Frameworks/libstdc++.6.dylib \
	SensPrecOptimizer.app/Contents/Frameworks/libstdc++.6.dylib

install_name_tool \
	-id @executable_path/../Frameworks/libSystem.B.dylib \
	SensPrecOptimizer.app/Contents/Frameworks/libSystem.B.dylib

install_name_tool \
	-id @executable_path/../Frameworks/libgcc_s.1.dylib \
	SensPrecOptimizer.app/Contents/Frameworks/libgcc_s.1.dylib


#library replacement using the install_name_tool - change
install_name_tool -change /Users/eagle/Qt5.1.1/5.1.1/clang_64/lib/QtCore.framework/Versions/5/QtCore \
        @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore \
        SensPrecOptimizer.app/Contents/MacOs/SensPrecOptimizer
        
install_name_tool -change /Users/eagle/Qt5.1.1/5.1.1/clang_64/lib/QtGui.framework/Versions/5/QtGui \
        @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui \
        SensPrecOptimizer.app/Contents/MacOs/SensPrecOptimizer

install_name_tool -change /Users/eagle/Qt5.1.1/5.1.1/clang_64/lib/QtWidgets.framework/Versions/5/QtWidgets \
        @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets \
        SensPrecOptimizer.app/Contents/MacOs/SensPrecOptimizer

install_name_tool -change /System/Library/Frameworks/OpenGL.framework/Versions/A/OpenGL \
        @executable_path/../Frameworks/OpenGL.framework/Versions/A/OpenGL \
        SensPrecOptimizer.app/Contents/MacOs/SensPrecOptimizer

install_name_tool -change /System/Library/Frameworks/AGL.framework/Versions/A/AGL \
        @executable_path/../Frameworks/AGL.framework/Versions/A/AGL \
        SensPrecOptimizer.app/Contents/MacOs/SensPrecOptimizer

install_name_tool -change /opt/local/lib/libboost_filesystem-mt.dylib \
        @executable_path/../Frameworks/libboost_filesystem-mt.dylib \
        SensPrecOptimizer.app/Contents/MacOs/SensPrecOptimizer

install_name_tool -change /opt/local/lib/libboost_system-mt.dylib \
        @executable_path/../Frameworks/libboost_system-mt.dylib \
        SensPrecOptimizer.app/Contents/MacOs/SensPrecOptimizer

install_name_tool -change /usr/lib/libstdc++.6.dylib \
        @executable_path/../Frameworks/libstdc++.6.dylib \
        SensPrecOptimizer.app/Contents/MacOs/SensPrecOptimizer

install_name_tool -change /usr/lib/libSystem.B.dylib \
        @executable_path/../Frameworks/libSystem.B.dylib \
        SensPrecOptimizer.app/Contents/MacOs/SensPrecOptimizer

install_name_tool -change /usr/lib/libgcc_s.1.dylib \
        @executable_path/../Frameworks/libgcc_s.1.dylib \
        SensPrecOptimizer.app/Contents/MacOs/SensPrecOptimizer


#link dependent libraries    
install_name_tool -change /Users/eagle/Qt5.1.1/5.1.1/clang_64/lib/QtCore.framework/Versions/5/QtCore \
        @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore \
        SensPrecOptimizer.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui
        
#install_name_tool -change /Users/eagle/Qt5.1.1/5.1.1/clang_64/lib/QtCore.framework/Versions/5/QtCore \
#        @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore \
#        SensPrecOptimizer.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets
        
#install_name_tool -change /Users/eagle/Qt5.1.1/5.1.1/clang_64/lib/QtGui.framework/Versions/5/QtGui \
#        @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui \
#        SensPrecOptimizer.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets

install_name_tool -change /System/Library/Frameworks/OpenGL.framework/Versions/A/OpenGL \
        @executable_path/../Frameworks/OpenGL.framework/Versions/A/OpenGL \
        SensPrecOptimizer.app/Contents/Frameworks/AGL.framework/Versions/A/AGL

install_name_tool -change /System/Library/Frameworks/OpenGL.framework/Versions/A/OpenGL \
        @executable_path/../Frameworks/OpenGL.framework/Versions/A/OpenGL \
        SensPrecOptimizer.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets

install_name_tool -change /System/Library/Frameworks/OpenGL.framework/Versions/A/OpenGL \
        @executable_path/../Frameworks/OpenGL.framework/Versions/A/OpenGL \
        SensPrecOptimizer.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui

install_name_tool -change /System/Library/Frameworks/AGL.framework/Versions/A/AGL \
        @executable_path/../Frameworks/AGL.framework/Versions/A/AGL \
        SensPrecOptimizer.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets

install_name_tool -change /System/Library/Frameworks/AGL.framework/Versions/A/AGL \
        @executable_path/../Frameworks/AGL.framework/Versions/A/AGL \
        SensPrecOptimizer.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui

install_name_tool -change /opt/local/lib/libboost_system-mt.dylib \
        @executable_path/../Frameworks/libboost_system-mt.dylib \
        SensPrecOptimizer.app/Contents/Frameworks/libboost_filesystem-mt.dylib



#print linked libraries
otool -L /Users/eagle/SensPrecOptimizer/SensPrecOptimizer.app/Contents/MacOS/SensPrecOptimizer 
