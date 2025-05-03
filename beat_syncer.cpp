#include "beat_syncer.h"
#include "modules/rubicon_core/conductor.h"
#include "core/math/math_funcs.h"

void BeatSyncer::set_enabled(bool p_enabled) {
    enabled = p_enabled;
}

bool BeatSyncer::get_enabled() const {
    return enabled;
}

void BeatSyncer::set_data(const Ref<BeatSyncerData> p_data) {
    if (!_data.is_null())
        _data->disconnect(SNAME("value_changed"), callable_mp(this, &BeatSyncer::_update_values));

    _data = p_data;
    if (_data.is_null())
        return;

    _data->connect(SNAME("value_changed"), callable_mp(this, &BeatSyncer::_update_values));
    _update_values();
}

Ref<BeatSyncerData> BeatSyncer::get_data() const {
    return _data;
}

void BeatSyncer::_notification(int p_notification) {
    switch(p_notification) {
        case NOTIFICATION_READY: {
            if (_initialized)
                return;

            _initialized = true;

            Conductor* conductor = Conductor::get_singleton();
            conductor->connect(SNAME("step_hit"), callable_mp(this, &BeatSyncer::_step_hit));
            conductor->connect(SNAME("time_change_reached"), callable_mp(this, &BeatSyncer::_time_change_reached));

            _time_change_reached(conductor->get_current_time_change());
        }   break;
        case NOTIFICATION_PREDELETE: {
            Conductor* conductor = Conductor::get_singleton();
            conductor->disconnect(SNAME("step_hit"), callable_mp(this, &BeatSyncer::_step_hit));
            conductor->disconnect(SNAME("time_change_reached"), callable_mp(this, &BeatSyncer::_time_change_reached));
        }   break;
    }
}

void BeatSyncer::_step_hit(const int p_step) {
    if (!enabled)
        return;

    if ((p_step - _step_offset) % _bump_step == 0)
        emit_signal("bumped");
}

void BeatSyncer::_time_change_reached(const Ref<TimeChange> p_current_time_change) {
    if (p_current_time_change.is_null())
        return;
    
    _step_offset += _current_time_change.is_null() ? 0 : int(Math::floor((p_current_time_change->time - _current_time_change->time) * _current_time_change->time_signature_numerator * _current_time_change->time_signature_denominator));

    _current_time_change = p_current_time_change;
    _update_values();
}

void BeatSyncer::_update_values() {
    if (!_initialized)
        _notification(NOTIFICATION_READY);
    
    if (_data.is_null() || _current_time_change.is_null())
        return;
    
    _bump_step = int(Math::floor(_current_time_change->time_signature_numerator * _current_time_change->time_signature_denominator * _data->get_value_as_measure()));
}

void BeatSyncer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_enabled", "enabled"), &BeatSyncer::set_enabled);
    ClassDB::bind_method("get_enabled", &BeatSyncer::get_enabled);
    ClassDB::bind_method(D_METHOD("set_data", "data"), &BeatSyncer::set_data);
    ClassDB::bind_method("get_data", &BeatSyncer::get_data);

    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "enabled"), "set_enabled", "get_enabled");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "data", PROPERTY_HINT_RESOURCE_TYPE, "BeatSyncerData"), "set_data", "get_data");

    ADD_SIGNAL(MethodInfo("bumped"));
}