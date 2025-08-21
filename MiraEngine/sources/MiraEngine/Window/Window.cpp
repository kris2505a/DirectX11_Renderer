#include <MiraPreCompHeader.h>
#include "Window.h"
#include <MiraEngine/Logging/Log.h>
#include <MiraEngine/Core/MiraMacros.h>

//Events
#include <MiraEngine/Event/KeyboardEvent.h>
#include <MiraEngine/Event/MouseEvent.h>
#include <MiraEngine/Event/WindowEvent.h>

namespace Mira {

Window::Window(const WinProcs& _procs)
	: m_procs(_procs), m_window(nullptr), m_isOpen(true), m_event({}) {

	m_window = new sf::RenderWindow({ m_procs.width, m_procs.height }, m_procs.title, sf::Style::Close);
}

Window::~Window() {
	delete m_window;
}

unsigned int Window::getWidth() const {
	return m_procs.width;
}

unsigned int Window::getHeight() const {
	return m_procs.height;
}

sf::RenderWindow* Window::getwindow() const {
	return m_window;
}

void Window::pollEvents() {
	while (m_window->pollEvent(m_event)) {
		switch (m_event.type) {
		
		case sf::Event::Closed:
		{
			WindowCloseEvent e;
			m_callback(e);
			m_isOpen = false;
		}	break;

		case sf::Event::KeyPressed:
		{
			KeyPressedEvent e(m_event.key.code, false);
			m_callback(e);
		}	break;

		case sf::Event::KeyReleased:
		{
			KeyReleasedEvent e(m_event.key.code);
			m_callback(e);
		}	break;

		case sf::Event::MouseMoved:
		{
			MouseMovedEvent e(m_event.mouseMove.x, m_event.mouseMove.y);
			m_callback(e);
		}	break;

		case sf::Event::MouseButtonPressed:
		{
			MouseButtonPressedEvent e(m_event.mouseButton.button);
			m_callback(e);
		}	break;

		case sf::Event::MouseButtonReleased:
		{
			MouseButtonReleasedEvent e(m_event.mouseButton.button);
			m_callback(e);
		}	break;

		case sf::Event::MouseWheelScrolled:
		{
			MouseScrolledEvent e(m_event.mouseWheel.x, m_event.mouseWheel.y);
			m_callback(e);
		}	break;
		}
	}
}

bool Window::isOpen() const {
	return m_isOpen;
}

void Window::setCallbackFn(const eventCallbackFn& fn) {
	m_callback = fn;
}

} //namespace ends