#include <freetype.h>
#include "sgui_widgets.hpp"

// events modeled after svg events
namespace internal{
void abort(sgui_widget* wg);
void activate(sgui_widget* wg);
bool begin(sgui::widget* wg);
void cancel(sgui::widget* wg);
void canplay(sgui::widget* wg);
void canplaythrough(sgui::widget* wg);
void change(sgui::widget* wg);
void click(sgui::widget* wg);
void close(sgui::widget* wg);
void cuechange(sgui::widget* wg);
void dblclick(sgui::widget* wg);
void drag(sgui::widget* wg);
void dragend(sgui::widget* wg);
void dragenter(sgui::widget* wg);
void dragleave(sgui::widget* wg);
void dragover(sgui::widget* wg);
void dragstart(sgui::widget* wg);
void drop(sgui::widget* wg);
void durationchange(sgui::widget* wg);
void emptied(sgui::widget* wg);
void end(sgui::widget* wg);
void ended(sgui::widget* wg);
void error(sgui::widget* wg);
void error(sgui::widget* wg);
void focus(sgui::widget* wg);
void focusin(sgui::widget* wg);
void focusout(sgui::widget* wg);
void input(sgui::widget* wg);
void invalid(sgui::widget* wg);
void keydown(sgui::widget* wg);
void keypress(sgui::widget* wg);
void keyup(sgui::widget* wg);
void load(sgui::widget* wg);
void loadeddata(sgui::widget* wg);
void loadedmetadata(sgui::widget* wg);
void loadstart(sgui::widget* wg);
void mousedown(sgui::widget* wg);
void mouseenter(sgui::widget* wg);
void mouseleave(sgui::widget* wg);
void mousemove(sgui::widget* wg);
void mouseout(sgui::widget* wg);
void mouseover(sgui::widget* wg);
void mouseup(sgui::widget* wg);
void mousewheel(sgui::widget* wg);
void pause(sgui::widget* wg);
void play(sgui::widget* wg);
void playing(sgui::widget* wg);
void progress(sgui::widget* wg);
void ratechange(sgui::widget* wg);
void repeat(sgui::widget* wg);
void reset(sgui::widget* wg);
void resize(sgui::widget* wg);
void resize(sgui::widget* wg);
void scroll(sgui::widget* wg);
void scroll(sgui::widget* wg);
void seeked(sgui::widget* wg);
void seeking(sgui::widget* wg);
void select(sgui::widget* wg);
void show(sgui::widget* wg);
void stalled(sgui::widget* wg);
void submit(sgui::widget* wg);
void suspend(sgui::widget* wg);
void timeupdate(sgui::widget* wg);
void toggle(sgui::widget* wg);
void unload(sgui::widget* wg);
void volumechange(sgui::widget* wg);
void waiting(sgui::widget* wg);
};




