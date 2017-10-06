#pragma once
#ifndef SM_TLSM_HPP
#define SM_TLSM_HPP

#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>

#include "application.hpp"
#include "menu_reactor.hpp"
#include "tlsm_events.hpp"

namespace sm {

// acronym for top-level state machine
struct _tlsm_t : boost::msm::front::state_machine_def<_tlsm_t> {
    sketchthis::application_t* app = {nullptr};

    struct menu : boost::msm::front::state<> {
        template <typename Event, typename FSM>
        void
        on_entry(const Event&, FSM& fsm)
        {
            fsm.app->set_reactor(sketchthis::menu_reactor(fsm.app));
        }

        template <typename Event, typename FSM>
        void
        on_exit(const Event&, FSM&)
        {
        }
    };

    struct canvas : boost::msm::front::state<> {
        template <typename Event, typename FSM>
        void
        on_entry(const Event&, FSM&)
        {
        }

        template <typename Event, typename FSM>
        void
        on_exit(const Event&, FSM&)
        {
        }
    };

    typedef menu initial_state;

    struct transition_table : boost::mpl::vector<
                                  // start, event, next, action, guard
                                  _row<menu, new_canvas, canvas>,
                                  _row<canvas, discard_canvas, menu>> {
    };

    // replaces the default no-transition response.
    template <typename FSM, typename Event>
    void
    no_transition(const Event&, FSM&, int)
    {
    }

    void
    set_app_ptr(sketchthis::application_t* arg_app)
    {
        app = arg_app;
    }
};
}

#endif // SM_TLSM_HPP