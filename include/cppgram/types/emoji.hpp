#ifndef __CPPGRAM_EMOJI_HPP
#define __CPPGRAM_EMOJI_HPP

#include <string>

// taken from: http://apps.timwhitlock.info/emoji/tables/unicode#emoji-modal

namespace cppgram
{
/**
 * \addtogroup Types
 * @{
 */

/**
 * \brief Contains static emoji. */
class Emoji
{
    /** @} */

    public:
    // faces
    static const std::string smileGrinning, smileLaughTearsOfJoy, smileOpenMouthEyes,
            smileOpenMouthClosedEyes, smileAndColdSweat, smileAndTightlyClosedEyes,
            smileWinkingFace, smileSweetClosedEyes, smileDelicious, relievedFace, smileHeartEyes,
            smirkingFace, unamusedFace, coldSweatFace, pensiveFace, confoundedFace, throwKissFace,
            kissingFace, winkingFaceStuckoutTongueFace, tightlyClosedEyesWinkingFace,
            disappointedFace, angryFace, poutingFace, cryingFace, perservingFace, triumphFace,
            disappointedButRelievedFace, fearfulFace, wearyFace, sleepyFace, tiredFace,
            loudCryingFace, openMouthAndColdSweatFace, screamingInFearFace, astonishedFace,
            flushedFace, dizzyFace, medicalMaskFace;

    // cats
    static const std::string smileCatGrinning, smileCatTearsOfJoy, smileCatOpenMouth,
            smileCatHeartEyes, smileCatFace, kissingCatFace, poutingCatFace, cryingCatFace,
            wearyCatFace;

    // gesture
    static const std::string notGoodGesture, isOkGesture, bowingDeeplyGesture, raisingHandGesture,
            raisingBothHandsGesture, frowningPersonGesture, poutingFacePersonGesture,
            foldedHandsPersonGesture;

    // monkeys
    static const std::string notSeeingMonkey, notHearingMonkey, notSpeakingMonkey;
};
}

#endif
