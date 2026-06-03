# ChatGPT Power Tools

ChatGPT Power Tools is an early-stage browser extension project for improving the ChatGPT web experience for power users. It focuses on practical workflow enhancements for long-running technical conversations, AI-assisted development, and multi-agent work while preserving the native ChatGPT interface.

## Why this project exists

ChatGPT conversations can become difficult to use when they grow into long technical sessions. Important prompts, decisions, checkpoints, headings, and follow-up tasks are often buried inside a large scrolling transcript. Power users who rely on ChatGPT for software development, research, writing, planning, or agent coordination need better navigation and reuse tools without replacing ChatGPT itself.

This project explores a progressive-enhancement approach: observe the rendered ChatGPT page, add small workflow-oriented controls, and keep the experience close to the product users already know.

## Core features / planned features

| Area | Goal | Example capabilities |
| --- | --- | --- |
| Executable Prompt Blocks | Detect reusable prompt blocks in assistant messages. | Copy prompt, open in a new ChatGPT conversation, run in Codex, export prompt, integrate with future agents. |
| Conversation Navigation | Make long conversations easier to move through. | Collapse/expand messages, collapse all / expand all, jump between user and assistant messages, keyboard navigation, visual markers. |
| Conversation Table of Contents | Provide a navigable structure for large conversations. | Sidebar generated from Markdown headings, chapter markers, assistant-generated structure, or future topic extraction. |
| Long Conversation Management | Help users understand and organize large sessions using observable data. | Message statistics, observable metadata, local indexing, topic grouping, search enhancements. |
| Search | Improve finding information inside long conversations. | Keyword search, heading search, message filtering, topic search, optional semantic search later. |
| Session Forking | Help users continue from a checkpoint in a fresh conversation. | Select checkpoint, generate continuation summary, open a new ChatGPT conversation, inject a continuation prompt. |

### Executable Prompt Blocks

One planned workflow is support for special Markdown code blocks that remain readable as plain text but can also be detected by the extension:

````markdown
```text(prompt)
Review the repository.

Expand lesson 3.

Do not modify future lessons.
```
````

These blocks are intended to act as reusable prompt units. The format should stay human-readable, copyable, and easy for browser extension code to detect without requiring a proprietary document format.

Potential actions include:

- Copying the prompt.
- Opening the prompt in a new ChatGPT conversation.
- Running the prompt in Codex where supported.
- Exporting the prompt for later use.
- Connecting the prompt to future agent integrations.

## Design principles

- **Progressive enhancement:** improve ChatGPT where possible without replacing the existing interface.
- **Native-feeling UI:** prefer injected buttons, side panels, overlays, keyboard shortcuts, and small controls that fit the ChatGPT experience.
- **Modular TypeScript architecture:** keep features isolated and maintainable.
- **Minimal dependency on undocumented APIs:** prefer rendered DOM, browser APIs, and public APIs when available.
- **Assume internal APIs are unstable:** avoid coupling core workflows to private ChatGPT endpoints.
- **Observable data only:** do not invent metrics that cannot be verified from the DOM, browser APIs, or public APIs.
- **Practical workflows over gimmicks:** prioritize features that reduce friction for heavy users.

## Architecture overview

The intended architecture is a Chrome-first browser extension written in TypeScript. The extension should be organized into small modules that can be developed and tested independently.

Suggested modules:

| Module | Responsibility |
| --- | --- |
| `prompt-runner` | Detect executable prompt blocks and expose actions such as copy, export, open in ChatGPT, or run in supported tools. |
| `collapsible-messages` | Add collapse/expand behavior and navigation controls for individual messages and full conversations. |
| `toc` | Build a conversation table of contents from headings, markers, generated structure, or extracted topics. |
| `search` | Provide conversation search, filtering, heading search, and future semantic search experiments. |
| `session-tools` | Support checkpointing, continuation summaries, and workflows for forking long sessions into new conversations. |

The extension should use DOM observation to discover relevant ChatGPT UI elements, then attach enhancements in a way that is resilient to interface changes. Browser APIs should be used for extension storage, keyboard shortcuts, tabs, and messaging where appropriate.

Primary target browser:

- Chrome

Secondary targets:

- Edge
- Brave
- Arc

## Current status

This project is currently early-stage and being bootstrapped. The repository does not yet contain a browser extension scaffold, `manifest.json`, `package.json`, TypeScript configuration, or build tooling.

The README defines the product direction, architecture principles, planned modules, and initial roadmap. Implementation details may change as the extension scaffold is introduced.

## Development setup

The repository is currently being bootstrapped. Development instructions will be added once the extension scaffold is committed.

No install, build, test, or browser-loading commands are documented yet because the repository does not currently include the required extension files or build configuration.

## Roadmap

| Phase | Focus | Outcome |
| --- | --- | --- |
| 1 | Extension scaffold | Add a Chrome extension foundation, TypeScript setup, manifest, local development workflow, and basic content script. |
| 2 | DOM observation layer | Establish reliable detection for conversation messages, Markdown content, headings, and code blocks using rendered page data. |
| 3 | Executable Prompt Blocks | Detect `text(prompt)` blocks and add copy/export/open actions. |
| 4 | Conversation Navigation | Add message collapse/expand controls, jump actions, and keyboard shortcuts. |
| 5 | Table of Contents | Build a sidebar from headings, markers, and conversation structure. |
| 6 | Search and filtering | Add keyword search, heading search, and message filtering for long conversations. |
| 7 | Session Forking | Prototype checkpoint selection and continuation prompt generation for starting fresh conversations. |
| 8 | Hardening | Improve resilience, accessibility, browser compatibility, settings, and documentation. |

## Non-goals

This project intentionally does not aim to:

- Replace the ChatGPT UI.
- Scrape private data unnecessarily.
- Depend heavily on undocumented internal ChatGPT APIs.
- Build arbitrary AI gimmicks unrelated to real workflow problems.
- Provide fake token counts, context usage numbers, or other metrics that cannot be verified.
- Become a general-purpose browser automation framework.

## License

This project is licensed under the MIT License. See [`LICENSE`](LICENSE) for details.
