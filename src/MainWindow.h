#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Common.h"
#include "MusicPlayerClient.h"
#include "PlaylistFile.h"
#include <QMainWindow>
#include <QModelIndex>
#include <vector>

namespace Ui {
class MainWindow;
}
class QTreeWidgetItem;
class QListWidgetItem;

class MainWindow : public BasicMainWindow
{
	Q_OBJECT
private:
	Ui::MainWindow *ui;
private:
	struct Private;
	Private *pv;
    QIcon folderIcon();
	void updatePlayingStatus();
	void updateCurrentSongIndicator();
	void updateTreeTopLevel();
	void updateTree(ResultItem *info);
	void clear();
	void updateServersComboBox();
	QString serverName() const;
	void showNotify(QString const &text);
	void showError(QString const &text);
	void set_volume_(int v);
	void loadPlaylist(QString const &name, bool replace);
	bool savePlaylist(QString const &name);
	bool deletePlaylist(QString const &name);
	void clearPlaylist();
	void invalidateCurrentSongIndicator();
	void execSongProperty(QString const &path, bool addplaylist);
	bool isPlaying() const;
	void execPrimaryCommand(QTreeWidgetItem *item);
	void updateStatusBar();
	QString songPath(QTreeWidgetItem const *item) const;
	QString songPath(QListWidgetItem const *item) const;
	void releaseMouseIfGrabbed();
	bool isPlaceHolder(QTreeWidgetItem *item) const;
	void on_edit_location();
	void startStatusThread();
	void stopStatusThread();
	void update(bool mpdupdate);
	void displayProgress(double elapsed);
	void seekProgressSlider(double elapsed, double total);
	void checkDisconnected();
	void execAddLocationDialog();
	void startSleepTimer(int mins);
	void stopSleepTimer();
	void execSleepTimerDialog();
	void disconnectNetwork();
	static QString makeStyleSheetText();
	static QString timeText(const MusicPlayerClient::Item &item);
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	bool isAutoReconnectAtStartup();

	bool execCommand(Command const &c);

	void preexec();
	void connectToMPD(Host const &host);
	void setRepeatEnabled(bool f);
	void setSingleEnabled(bool f);
	void setConsumeEnabled(bool f);
	void setRandomEnabled(bool f);

	void play();
	void pause();
	void stop();
	void play(bool toggle);

	void eatMouse();
protected:
	virtual bool event(QEvent *event);
	virtual bool eventFilter(QObject *, QEvent *);
	virtual void keyPressEvent(QKeyEvent *);
	void changeEvent(QEvent *e);
	virtual void closeEvent(QCloseEvent *);
	bool updatePlaylist();
	void refreshTreeItem(QTreeWidgetItem *item);
	void deleteSelectedSongs();
	void addToPlaylist(QString const &path, int to, bool update);
	virtual void mouseReleaseEvent(QMouseEvent *);
//	virtual void timerEvent(QTimerEvent *);
	void deletePlaylistItem(QListWidgetItem *item, bool updateplaylist);
private slots:
	void on_toolButton_play_clicked();
	void on_treeWidget_itemExpanded(QTreeWidgetItem *item);
	void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

	void onVolumeChanged();
	void onSliderPressed();
	void onSliderReleased();

	void onTreeViewContextMenuEvent(QContextMenuEvent *);
	void onListViewContextMenuEvent(QContextMenuEvent *);
	void onDropEvent(bool done);
	void on_listWidget_playlist_doubleClicked(const QModelIndex &index);
	void on_toolButton_stop_clicked();
	void on_toolButton_prev_clicked();
	void on_toolButton_next_clicked();
	void on_toolButton_repeat_clicked();
	void on_toolButton_random_clicked();
	void on_toolButton_volume_clicked();
	void on_toolButton_sleep_timer_clicked();

	void on_action_debug_triggered();
	void on_action_play_triggered();
	void on_action_stop_triggered();
	void on_action_previous_triggered();
	void on_action_next_triggered();
	void on_action_repeat_triggered();
	void on_action_random_triggered();
	void on_action_help_about_triggered();
	void on_action_edit_delete_triggered();
	void on_action_network_connect_triggered();
	void on_action_network_disconnect_triggered();
	void on_action_network_reconnect_triggered();
	void on_horizontalSlider_valueChanged(int value);
	void on_action_single_triggered();
	void on_action_consume_triggered();
	void on_toolButton_single_clicked();
	void on_action_edit_cut_triggered();
	void on_action_edit_copy_triggered();
	void on_action_edit_paste_bottom_triggered();
	void on_pushButton_manage_connections_clicked();
	void on_action_edit_paste_insert_triggered();
	void on_comboBox_currentIndexChanged(int index);
	void on_action_playlist_add_location_triggered();
	void on_action_playlist_update_triggered();
	void on_action_file_close_triggered();
	void on_action_playlist_quick_save_1_triggered();
	void on_action_playlist_quick_save_2_triggered();
	void on_action_playlist_quick_load_1_triggered();
	void on_action_playlist_quick_load_2_triggered();
	void on_action_playlist_clear_triggered();
	void on_action_playlist_edit_triggered();
	void on_action_edit_keyboard_customize_triggered();
	void on_action_playlist_unify_triggered();
	void on_toolButton_consume_clicked();
	void onUpdateStatus();


	void on_action_sleep_timer_triggered();

public:
	static QString tr_Module_information_could_not_be_acquired()
	{
		return tr("Module information could not be acquired.");
	}

	// QWidget interface
	void unify();
protected:

	// QObject interface
protected:
	void timerEvent(QTimerEvent *);
};

#endif // MAINWINDOW_H
