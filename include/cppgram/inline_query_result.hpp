#ifndef CPPGRAM_INLINE_QUERY_RESULT_HPP
#define CPPGRAM_INLINE_QUERY_RESULT_HPP

#include <json/json.h>
#include <string>

namespace cppgram
{
enum EParseMode : short;

/**
 * \brief Create articles to send as inlineQuery result
 * \details Helper class to create articles and pass the results to
 * answerInlineQuery
 */
class InlineQueryResult
{
    public:
    /*! \fn InlineQueryResult::InlineQueryResult()
     * \brief InlineQueryResult constructor
     * @return A new object
     */
    InlineQueryResult();

    /**
     * \brief Add a new article to the results
     * @param title Title of the result
     * @param message_text Text of the message to be sent, 1-4096 characters
     * @param reply_markup <i>Optional</i>. Inline keyboard attached to the
     * message
     * @param description <i>Optional</i>. Short description of the result
     * @param parse_mode Optional. Formatting option
     * @param disable_web_page_preview <i>Optional</i>. Disables link previews for
     * links in the sent message
     * @return Id of the article
     */
    short newArticle( const std::string &title,
                      const std::string &message_text,
                      const Json::Value &reply_markup             = Json::Value(),
                      const std::string &description              = "",
                      const EParseMode   parse_mode               = static_cast<EParseMode>( 1 ),
                      const bool         disable_web_page_preview = true );

    short newArticle( const std::string &title,
                      const std::string &message_text,
                      const std::string &description,
                      const Json::Value &reply_markup             = Json::Value(),
                      const EParseMode   parse_mode               = static_cast<EParseMode>( 0 ),
                      const bool         disable_web_page_preview = true,
                      const std::string &url                      = "",
                      const bool         hide_url                 = false,
                      const std::string &thumb_url                = "",
                      const int_fast32_t thumb_width              = 0,
                      const int_fast32_t thumb_height             = 0 );

    /**
     * \brief Get results to send in answerInlineQuery
     * @return The JSON containing the results
     */
    const Json::Value &getResults() const;

    private:
    Json::Value results;
    short       articleId;
};
}

#endif
