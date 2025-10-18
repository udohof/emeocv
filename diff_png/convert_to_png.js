const puppeteer = require('puppeteer');
const fs = require('fs');
const path = require('path');

async function convertHtmlToPng() {
    const browser = await puppeteer.launch({
        headless: true,
        args: ['--no-sandbox', '--disable-setuid-sandbox']
    });
    
    const page = await browser.newPage();
    await page.setViewport({ width: 1200, height: 800 });
    
    // Get all HTML files in the current directory
    const htmlFiles = fs.readdirSync(__dirname)
        .filter(file => file.endsWith('.html'))
        .sort();
    
    console.log(`Found ${htmlFiles.length} HTML files to convert:`);
    
    for (const htmlFile of htmlFiles) {
        const htmlPath = path.join(__dirname, htmlFile);
        const pngFile = htmlFile.replace('.html', '.png');
        const pngPath = path.join(__dirname, pngFile);
        
        console.log(`Converting: ${htmlFile} -> ${pngFile}`);
        
        try {
            await page.goto(`file://${htmlPath}`, { waitUntil: 'networkidle0' });
            
            // Wait for content to load completely
            await page.waitForSelector('body', { timeout: 10000 });
            await new Promise(resolve => setTimeout(resolve, 2000));
            
            // Take screenshot of the whole page
            await page.screenshot({
                path: pngPath,
                fullPage: true,
                type: 'png'
            });
            
            console.log(`✓ Successfully created: ${pngFile}`);
        } catch (error) {
            console.error(`✗ Error converting ${htmlFile}:`, error.message);
        }
    }
    
    await browser.close();
    console.log('\n✓ All conversions completed!');
}

convertHtmlToPng().catch(console.error);