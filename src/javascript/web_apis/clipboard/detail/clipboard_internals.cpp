#include "clipboard_internals.hpp"

#include "ext/pair.hpp"
#include "javascript/environment/realms_2.hpp"

#include "clipboard/clipboard_item.hpp"

#include <QtCore/QMimeData>
#include <QtGui/QClipboard>
#include <QtWidgets/QApplication>

#include <range/v3/to_container.hpp>
#include <range/v3/view/transform.hpp>


auto clipboard::detail::system_clipboard()
        -> QClipboard*
{
    return qobject_cast<QApplication*>(QApplication::instance())->clipboard();
}


//auto clipboard::detail::system_clipboard_data()
//        -> ext::map<ext::string, clipboard_item_data_t>
//{
//    decltype(auto) qt_mime_data = system_clipboard()->mimeData();
//    decltype(auto) qt_mime_data_formats = qt_mime_data->formats();
//
//    decltype(auto) cpp_data_pairs = qt_mime_data_formats | ranges::views::transform(
//            [qt_mime_data]<typename T>(T&& type) mutable
//            {return ext::make_pair(type, qt_mime_data->data(std::forward<T>(type)));});
//
//    decltype(auto) v8_data_pairs = cpp_data_pairs | ranges::views::transform(
//            []<typename T>(T&& data) mutable
//            {return ext::make_pair(data.first, clipboard_item_data_t{data.second});});
//
//    return v8_data_pairs | ranges::to<ext::map<ext::string, clipboard_item_data_t>>;
//}
