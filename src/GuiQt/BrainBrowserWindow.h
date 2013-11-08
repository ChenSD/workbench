
#ifndef __BRAIN_BROWSER_WINDOW_H__
#define __BRAIN_BROWSER_WINDOW_H__

/*LICENSE_START*/
/*
 *  Copyright 1995-2002 Washington University School of Medicine
 *
 *  http://brainmap.wustl.edu
 *
 *  This file is part of CARET.
 *
 *  CARET is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  CARET is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CARET; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <stdint.h>

#include <QImage>
#include <QMainWindow>

#include "AString.h"
#include "DataFileException.h"
#include "DataFileTypeEnum.h"
#include "SceneableInterface.h"
#include "TileTabsConfiguration.h"

class QAction;
class QActionGroup;
class QDockWidget;
class QMenu;

namespace caret {
    class BrainBrowserWindowToolBar;
    class BrainBrowserWindowOrientedToolBox;
    class BrainOpenGLWidget;
    class BrowserTabContent;
    class SceneClassAssistant;

    
    /**
     * The brain browser window is the viewer for
     * brain models.  It may contain multiple tabs
     * with each tab displaying brain models.
     */ 
    class BrainBrowserWindow : public QMainWindow, public SceneableInterface  {
        Q_OBJECT
        
    public:
        virtual ~BrainBrowserWindow();
        
        BrowserTabContent* getBrowserTabContent();

        BrowserTabContent* getBrowserTabContent(int tabIndex);

        
        QMenu* createPopupMenu();
        
        void removeAndReturnAllTabs(std::vector<BrowserTabContent*>& allTabContent);
        
        int32_t getBrowserWindowIndex() const;

        bool isTileTabsSelected() const;
        
        /**
         * Mode for loading spec files
         */
        enum LoadSpecFileMode {
            /** Do not show spec file dialog, just load all files listed in spec file listed on command line at program startup */
            LOAD_SPEC_FILE_CONTENTS_VIA_COMMAND_LINE,
            /** Show spec file in spec file dialog for user selections */
            LOAD_SPEC_FILE_WITH_DIALOG,
            /** Show spec file in spec file dialog for user selections from spec file listed on command line at program startup */
            LOAD_SPEC_FILE_WITH_DIALOG_VIA_COMMAND_LINE
        };
        
        void loadFilesFromCommandLine(const std::vector<AString>& filenames,
                                      const LoadSpecFileMode loadSpecFileMode);
        
        void loadSceneFromCommandLine(const AString& sceneFileName,
                                      const AString& sceneNameOrNumber);
        
        bool loadFilesFromNetwork(QWidget* parentForDialogs,
                                  const std::vector<AString>& filenames,
                                  const std::vector<DataFileTypeEnum::Enum> dataFileTypes,
                                  const AString& username,
                                  const AString& password);
        
        virtual SceneClass* saveToScene(const SceneAttributes* sceneAttributes,
                                        const AString& instanceName);
        
        virtual void restoreFromScene(const SceneAttributes* sceneAttributes,
                                      const SceneClass* sceneClass);

        void getViewportSize(int &w, int &h);
        
        TileTabsConfiguration* getSelectedTileTabsConfiguration();
        
        void setSelectedTileTabsConfiguration(TileTabsConfiguration* configuration);
        
        void resetGraphicsWidgetMinimumSize();
        
        void setGraphicsWidgetFixedSize(const int32_t width,
                                        const int32_t height);
        
        void getGraphicsWidgetSize(int32_t& widthOut,
                                   int32_t& heightOut) const;
        
    protected:
        void closeEvent(QCloseEvent* event);
        void keyPressEvent(QKeyEvent* event);
        
    private slots:        
        void processAboutWorkbench();
        void processInformationDialog();
        void processNewWindow();
        void processNewTab();
        void processDataFileLocationOpen();
        void processDataFileOpen();
        void processManageSaveLoadedFiles();
        void processCaptureImage();
        void processRecordMovie();
        void processEditPreferences();
        void processCloseSpecFile();
        void processExitProgram();
        void processMoveAllTabsToOneWindow();
        void processViewFullScreenSelected();
        void processViewTileTabs();
        void processViewTileTabsConfigurationDialog();
        
        void processMoveOverlayToolBoxToLeft();
        void processMoveOverlayToolBoxToBottom();
        void processMoveOverlayToolBoxToFloat();
        void processHideOverlayToolBox();
        
        void processMoveFeaturesToolBoxToRight();
        void processMoveFeaturesToolBoxToFloat();
        void processHideFeaturesToolBox();
        
        void processMoveSelectedTabToWindowMenuAboutToBeDisplayed();
        void processMoveSelectedTabToWindowMenuSelection(QAction*);
        
        void processRecentSpecFileMenuAboutToBeDisplayed();
        void processRecentSpecFileMenuSelection(QAction*);
        
        void processShowOverlayToolBox(bool);
        void processShowFeaturesToolBox(bool);
        void processOverlayHorizontalToolBoxVisibilityChanged(bool);
        void processOverlayVerticalToolBoxVisibilityChanged(bool);
        
        void processFileMenuAboutToShow();
        void processDataMenuAboutToShow();
        void processViewMenuAboutToShow();
        
        void processTileTabsMenuAboutToBeDisplayed();
        void processTileTabsMenuSelection(QAction*);
        
        void processSurfaceMenuInformation();
        void processSurfaceMenuVolumeInteraction();
        
        void processConnectToAllenDataBase();
        void processConnectToConnectomeDataBase();
        
        void processHcpWebsiteInBrowser();
        void processHcpFeatureRequestWebsiteInBrowser();
        
        void processShowSurfacePropertiesDialog();
        
        void processDevelopGraphicsTiming();
        
        void processDevelopExportVtkFile();
        
        void processProjectFoci();
        
    private:
        // Contains status of components such as enter/exit full screen
        struct WindowComponentStatus {
            bool isFeaturesToolBoxDisplayed;
            bool isOverlayToolBoxDisplayed;
            bool isToolBarDisplayed;
            QByteArray windowState;
            QByteArray windowGeometry;
            QByteArray featuresGeometry;
        };
        
        enum CreateDefaultTabsMode {
            CREATE_DEFAULT_TABS_YES,
            CREATE_DEFAULT_TABS_NO
        };
        
        BrainBrowserWindow(const int browserWindowIndex,
                           BrowserTabContent* browserTabContent,
                           const CreateDefaultTabsMode createDefaultTabsMode,
                           QWidget* parent = 0,
                           Qt::WindowFlags flags = 0);
        
        BrainBrowserWindow(const BrainBrowserWindow&);
        BrainBrowserWindow& operator=(const BrainBrowserWindow&);
        
        bool loadFiles(QWidget* parentForDialogs,
                       const std::vector<AString>& filenames,
                       const std::vector<DataFileTypeEnum::Enum> dataFileTypes,
                       const LoadSpecFileMode loadSpecFileMode,
                       const AString& username,
                       const AString& password);
        
        void createActions();
        void createActionsUsedByToolBar();
        void createMenus();
        
        QMenu* createMenuDevelop();
        QMenu* createMenuFile();
        QMenu* createMenuView();
        QMenu* createMenuViewMoveOverlayToolBox();
        QMenu* createMenuViewMoveFeaturesToolBox();
        QMenu* createMenuConnect();
        QMenu* createMenuData();
        QMenu* createMenuSurface();
        QMenu* createMenuVolume();
        QMenu* createMenuWindow();
        QMenu* createMenuHelp();
        
        void moveOverlayToolBox(Qt::DockWidgetArea area);
        void moveFeaturesToolBox(Qt::DockWidgetArea area);
        
        void restoreWindowComponentStatus(const WindowComponentStatus& wcs);
        void saveWindowComponentStatus(WindowComponentStatus& wcs);
        
        void openSpecFile(const AString& specFileName) throw (DataFileException);
        
        void processViewFullScreen(bool showFullScreenDisplay,
                                   const bool saveRestoreWindowStatus);
        
        void setViewTileTabs(const bool newStatus);
        
        /** Index of this window */
        int32_t m_browserWindowIndex;
        
        BrainOpenGLWidget* m_openGLWidget;
        
        BrainBrowserWindowToolBar* m_toolbar;
        
        QAction* m_aboutWorkbenchAction;
        
        QAction* m_newWindowAction;
        
        QAction* m_newTabAction;
        
        QAction* m_openFileAction;
        
        QAction* m_openLocationAction;
        
        QAction* m_manageFilesAction;
        
        QAction* m_closeSpecFileAction;
        
        QAction* m_closeTabAction;
        
        QAction* m_closeWindowAction;
        
        QAction* m_captureImageAction;

        QAction* m_recordMovieAction;
        
        QAction* m_preferencesAction;
        
        QAction* m_exitProgramAction;
        
        QAction* m_showToolBarAction;
        
        QMenu* m_viewMoveFeaturesToolBoxMenu;
        QMenu* m_viewMoveOverlayToolBoxMenu;
        
        QAction* m_viewFullScreenAction;
        QAction* m_viewTileTabsAction;
        bool m_viewTileTabsSelected;
        
        QMenu* m_tileTabsMenu;
        QAction* m_createAndEditTileTabsAction;
        
        QAction* m_nextTabAction;
        
        QAction* m_previousTabAction;
        
        QAction* m_renameSelectedTabAction;
        
        QAction* m_moveTabsInWindowToNewWindowsAction;
        
        QAction* m_moveTabsFromAllWindowsToOneWindowAction;
        
        QAction* m_bringAllToFrontAction;
        QAction* m_tileWindowsAction;
        
        QAction* m_informationDialogAction;
        
        QAction* m_connectToAllenDatabaseAction;
        QAction* m_connectToConnectomeDatabaseAction;

        QAction* m_helpHcpWebsiteAction;
        QAction* m_helpHcpFeatureRequestAction;
        QAction* m_helpOnlineAction;
        QAction* m_helpSearchOnlineAction;
        
        QAction* m_developerGraphicsTimingAction;
        QAction* m_developerExportVtkFileAction;
        
        QAction* m_overlayToolBoxAction;
        
        QAction* m_featuresToolBoxAction;
        
        QAction* m_fociProjectAction;
        
        QMenu* m_moveSelectedTabToWindowMenu;
        
        QMenu* m_recentSpecFileMenu;
        
        BrainBrowserWindowOrientedToolBox* m_overlayHorizontalToolBox;
        BrainBrowserWindowOrientedToolBox* m_overlayVerticalToolBox;
        BrainBrowserWindowOrientedToolBox* m_overlayActiveToolBox;
        BrainBrowserWindowOrientedToolBox* m_featuresToolBox;
        
        AString m_selectedTileTabsConfigurationUniqueIdentifier;
        TileTabsConfiguration* m_defaultTileTabsConfiguration;
        
        static AString s_previousOpenFileNameFilter;
        static AString s_previousOpenFileDirectory;
        
        WindowComponentStatus m_defaultWindowComponentStatus;
        WindowComponentStatus m_normalWindowComponentStatus;
                
        static bool s_firstWindowFlag;
        
        friend class BrainBrowserWindowToolBar;
        friend class GuiManager;
        
        SceneClassAssistant* m_sceneAssistant;
        
        /** X position from scene file for first window */
        static int32_t s_sceneFileFirstWindowX;

        /** Y position from scene file for first window */
        static int32_t s_sceneFileFirstWindowY;
        
    };
#ifdef __BRAIN_BROWSER_WINDOW_DECLARE__
    AString BrainBrowserWindow::s_previousOpenFileNameFilter;
    AString BrainBrowserWindow::s_previousOpenFileDirectory;
    bool BrainBrowserWindow::s_firstWindowFlag = true;
    int32_t BrainBrowserWindow::s_sceneFileFirstWindowX = -1;
    int32_t BrainBrowserWindow::s_sceneFileFirstWindowY = -1;
#endif // __BRAIN_BROWSER_WINDOW_DECLARE__
    
}

#endif // __BRAIN_BROWSER_WINDOW_H__

