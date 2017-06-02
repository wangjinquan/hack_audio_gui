#ifndef HACK_AUDIO_VIEWPORT_H
#define HACK_AUDIO_VIEWPORT_H

#include "../utils/hack_audio_NavigationButton.h"

namespace HackAudio
{

/**
 An unbounded, infinitely-scrollable viewport for displaying HackAudio::Diagram components
*/

class Viewport : public juce::Component,
                 private juce::ComponentListener,
                 private juce::ButtonListener
{

public:

    Viewport();
    ~Viewport();

    /**
     Sets the top-level diagram to display, clearing out any traversal chains
    */
    void setDiagram(HackAudio::Diagram& d);

    /**
     Removes any diagrams from the display
    */
    void clearDiagram();

    /**
     Move downwards to a specific diagram, marking the current one as the last parent
    */
    void traverseDown(HackAudio::Diagram& d);

    /**
     Move up to the next parent diagram
    */
    void traverseUp();

    /**
     Return to the top level diagram
    */
    void traverseTop();

    /** 
     Returns true if the diagram is within the traversal chain
     */
    bool isInTraversal(HackAudio::Diagram& d) const;

private:

    void setDiagramViaTraversal(HackAudio::Diagram& d);

    void mouseEnter    (const juce::MouseEvent& e) override;
    void mouseExit     (const juce::MouseEvent& e) override;
    void mouseDown     (const juce::MouseEvent& e) override;
    void mouseDrag     (const juce::MouseEvent& e) override;
    void mouseUp       (const juce::MouseEvent& e) override;
    void mouseWheelMove(const juce::MouseEvent& e, const juce::MouseWheelDetails& w) override;

    void enablementChanged() override;

    void buttonClicked(juce::Button* b) override;

    void componentMovedOrResized(juce::Component& component, bool wasMoved, bool wasResized) override;

    void paint(juce::Graphics& g) override;
    void paintOverChildren(juce::Graphics& g) override;

    void resized() override;

    juce::Component contentContainer;
    HackAudio::Diagram* currentContent;

    juce::Array<HackAudio::Diagram*> parentContent;

    NavigationButton backButton;
    NavigationButton topButton;

    juce::ComponentDragger componentDragger;
    juce::ComponentAnimator componentAnimator;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Viewport)

};

}

#endif
