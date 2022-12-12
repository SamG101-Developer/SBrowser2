export module apis._3ds.types;

import ext.any;
import ext.map;
import ext.string;


export namespace three_ds::detail
{
    enum class three_ds_challenge_ind {REQUESTED, MANDATED, NONE};

    using three_ds_request = ext::map<ext::string, ext::any>;
    using three_ds_response = ext::map<ext::string, ext::any>;
}
