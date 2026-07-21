cmake_minimum_required(VERSION 3.16)

project(slay_the_spire VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(slay_the_spire
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Page.h
        login.h login.cpp login.ui
        player.h player.cpp
        card.h card.cpp
        buff_debuff.h buff_debuff.cpp
        potion.h potion.cpp
        relic.h relic.cpp
        mainmenu.h mainmenu.cpp mainmenu.ui
        background.qrc
        startmenu.h startmenu.cpp
        leaderboard.h leaderboard.cpp
        settingspage.h settingspage.cpp
        statusbar.h statusbar.cpp
        map1.h map1.cpp map1.ui
        room.h room.cpp
        enemyroom.h enemyroom.cpp
        eliteroom.h eliteroom.cpp
        eventroom.h eventroom.cpp
        treasureroom.h treasureroom.cpp
        campfireroom.h campfireroom.cpp
        shoproom.h shoproom.cpp
        bossroom.h bossroom.cpp

        screensize.h screensize.cpp
        RoomEnum.h
        enemyscene.h enemyscene.cpp enemyscene.ui
        elitescene.h elitescene.cpp elitescene.ui
        eventscene.h eventscene.cpp eventscene.ui
        treasurescene.h treasurescene.cpp treasurescene.ui
        campscene.h campscene.cpp campscene.ui
        shopscene.h shopscene.cpp shopscene.ui
        bossscene.h bossscene.cpp bossscene.ui
        Soundtrack.qrc
        attackcrads.qrc
        attack_cards.h attack_cards.cpp
        enemy.h enemy.cpp
        strike.h strike.cpp
        twinstrike.h twinstrike.cpp
        bloodforblood.h bloodforblood.cpp
        hemokinesis.h hemokinesis.cpp
        carnage.h carnage.cpp
        whirlwind.h whirlwind.cpp
        bludgeon.h bludgeon.cpp
        immolate.h immolate.cpp
        reaper.h reaper.cpp
        feed.h feed.cpp
	redx.h redx.cpp
        roomscene.h roomscene.cpp
        combatscene.h combatscene.cpp
        avatar.qrc
        event.h event.cpp
        goldenidolevent.h goldenidolevent.cpp
        goldenshrineevent.h goldenshrineevent.cpp
        labevent.h labevent.cpp
        serpantevent.h serpantevent.cpp
        facetraderevent.h facetraderevent.cpp
        joustevent.h joustevent.cpp
        ominousforgeevent.h ominousforgeevent.cpp
        augmenterevent.h augmenterevent.cpp






    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET slay_the_spire APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(slay_the_spire SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(slay_the_spire
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(slay_the_spire PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.slay_the_spire)
endif()
set_target_properties(slay_the_spire PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS slay_the_spire
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(slay_the_spire)
endif()
