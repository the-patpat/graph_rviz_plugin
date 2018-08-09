#ifndef GRAPH_RVIZ_PLUGIN_PANEL_HPP
#define GRAPH_RVIZ_PLUGIN_PANEL_HPP

#include <atomic>
#include <chrono>
#include <deque>
#include <memory>
#include <mutex>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <ros/ros.h>
#include <ros/service.h>
#include <ros/time.h>
#include <graph_rviz_plugin/configure_graph.hpp>
#include <graph_rviz_plugin/configure.hpp>
#include <graph_rviz_plugin/qcustomplot.h>
#include <graph_rviz_plugin/selection_topics.hpp>
#include <graph_rviz_plugin/topic_data.hpp>
#include <graph_rviz_plugin/topic_color.hpp>
#include <rviz/panel.h>
#include <thread>

namespace graph_rviz_plugin
{

class GraphPanel : public rviz::Panel
{
  Q_OBJECT

public:
  GraphPanel(QWidget *parent = 0);
  virtual ~GraphPanel();

Q_SIGNALS:
  void enable(const bool);
  void displayMessageBox(const QString,
                         const QString,
                         const QString,
                         const QMessageBox::Icon);

protected Q_SLOTS:
  void displayMessageBoxHandler(const QString title,
                                const QString text,
                                const QString info = "",
                                const QMessageBox::Icon icon = QMessageBox::Icon::Information);
  virtual void load(const rviz::Config &config);
  virtual void save(rviz::Config config) const;
  void startPauseClicked();
  void stopClicked();
  void topicsSelectionClicked();
  void graphSettingsClicked();
  void settingsClicked();
  void resetClicked();
  void graphUpdate();
  void graphSettingsUpdate();
  void enableLegend(bool legend_enable);
  void graphInit();

private:
  std::shared_ptr<ros::NodeHandle> nh_;
  QPushButton *start_pause_button_;
  QPushButton *topic_button_;
  QPushButton *stop_button_;
  QPushButton *graph_settings_button_;
  QTimer *graph_refresh_timer_;
  TopicColor topic_color_class_;
  QCustomPlot *plot_;
  std::deque<std::shared_ptr<TopicData>> displayed_topics_;
  std::atomic<bool> legend_enable_;
  std::atomic<bool> yaxis_rescale_auto_;
  std::atomic<bool> window_time_enable_;
  std::atomic<bool> graph_stopped_;
  double y_min_ = 0;
  double y_max_ = 1;
  double w_time_ = 1;
  double refresh_period_ms_ = 16; // in milliseconds
};

}

#endif
